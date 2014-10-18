#include <QDebug>
#include <Client/Client.hpp>
#include <Message/Message/StartGame/StartGame.hpp>
#include <Message/MessageHeader/MessageHeader.hpp>
#include <Message/MessageParser/MessageParser.hpp>
#include <Message/Message/GameStarted/GameStarted.hpp>
#include <Message/Message/Move/Move.hpp>
#include <Message/Message/FieldData/FieldData.hpp>
#include <Message/Message/ScoreData/ScoreData.hpp>

Client::Client ( int& argc , char** argv ):
    QApplication(argc,argv)
{
    this->initializeInterface();
    this->initializeNetworkManager();
    this->initializeInputManager();
}

void Client::initializeInterface ( void )
{

    this->interface.show();

    QObject::connect
    (
        &this->interface,
        SIGNAL(exitGame()),
        this,
        SLOT(exitGame())
    );

    QObject::connect
    (
        &this->interface,
        SIGNAL(startGame()),
        this,
        SLOT(startGame())
    );

    QObject::connect
    (
        &this->interface,
        SIGNAL(move(MoveDirection)),
        this,
        SLOT(move(MoveDirection))
    );

    QObject::connect
    (
        this,
        SIGNAL(gameStarted()),
        &this->interface,
        SLOT(gameStarted())
    );

    QObject::connect
    (
        this,
        SIGNAL(fieldDataReceived(FieldData*)),
        &this->interface,
        SIGNAL(fieldDataReceived(FieldData*))
    );

    QObject::connect
    (
        this,
        SIGNAL(scoreDataReceived(ScoreData*)),
        &this->interface,
        SIGNAL(scoreDataReceived(ScoreData*))
    );

    QObject::connect
    (
        this,
        SIGNAL(gameEnded()),
        &this->interface,
        SIGNAL(gameEnded())
    );

}

void Client::initializeNetworkManager ( void )
{

    QObject::connect
    (
        &this->networkManager,
        SIGNAL(connected()),
        &this->interface,
        SLOT(connected())
    );

    QObject::connect
    (
        &this->networkManager,
        SIGNAL(disconnected()),
        &this->interface,
        SLOT(disconnected())
    );

    QObject::connect
    (
        &this->networkManager,
        SIGNAL(messageReceived(Message*)),
        this,
        SLOT(processMessage(Message*))
    );

    this->networkManager.connectToServer();

}

void Client::initializeInputManager()
{

    // Input manager listens to the interface events
    this->interface.installEventFilter(&this->inputManager);

    QObject::connect
    (
        &this->inputManager,
        SIGNAL(sampled(MoveDirection)),
        this,
        SLOT(move(MoveDirection))
    );

}

void Client::exitGame ( void )
{
    this->exit();
}

void Client::startGame ( void )
{
    this->networkManager.sendMessage(StartGame());
}

void Client::move ( MoveDirection moveDirection )
{
    Move messageMove(moveDirection);
    this->networkManager.sendMessage(messageMove);
}

void Client::processMessage ( Message* messagePtr )
{

    // Message was parsed. Get it's header
    MessageHeader messageHeader = messagePtr->getHeader();

    // Act basing on the message header
    switch ( messageHeader )
    {

        // Game started
        case MessageHeader::GameStartedHeader :
        {
            this->inputManager.enable();
            emit this->gameStarted();
            break;
        }

        // Game ended
        case MessageHeader::GameEndedHeader :
        {
            this->inputManager.disable();
            emit this->gameEnded();
            break;
        }

        // Field data
        case MessageHeader::FieldDataHeader :
        {
            static quint64 timestamp = 0;

            FieldData* fieldDataPtr = reinterpret_cast<FieldData*>(messagePtr);


            quint64 timestampNew = fieldDataPtr->getTimestamp();
            if ( timestampNew < timestamp )
            {
                qDebug() << "Ooooops";
            }
            timestamp = timestampNew;


            emit this->fieldDataReceived(fieldDataPtr);
            break;
        }

        // Score data
        case MessageHeader::ScoreDataHeader :
        {
            ScoreData* scoreDataPtr = reinterpret_cast<ScoreData*>(messagePtr);
            emit this->scoreDataReceived(scoreDataPtr);
            break;
        }

        // Just to make the compiler shut the fuck up
        default:
        {
            break;
        }

    }

    delete messagePtr;

}
