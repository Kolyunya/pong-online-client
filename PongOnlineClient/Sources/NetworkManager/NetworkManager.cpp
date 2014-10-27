#include <NetworkManager/NetworkManager.hpp>
#include <Message/Message/HandshakeRequest/HandshakeRequest.hpp>
#include <Message/Message/HandshakeResponse/HandshakeResponse.hpp>
#include <Message/Message/HandshakeAck/HandshakeAck.hpp>
#include <Message/Message/Delimiter/Delimiter.hpp>
#include <Message/MessageParser/MessageParser.hpp>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QException>
#include <QSettings>

NetworkManager::NetworkManager ( QObject* parentPtr ) :
    QObject(parentPtr),
    isActive(false),
    isConnected(false)
{
    this->initializeServerCredentials();
    this->initializeHandshakeTimer();
    this->initializeUdpSocket();
    this->initializeTcpSocket();
}

NetworkManager::~NetworkManager ( void ) noexcept
{
    this->disconnectFromServer();
}

bool NetworkManager::getConnectionState ( void ) const
{

    return this->isConnected;

}

void NetworkManager::connectToServer ( void )
{

    // Activate the manager
    this->isActive = true;

    // Connect to the server
    this->tcpSocket.connectToHost
    (
        this->serverAddress,
        this->serverPort
    );

}

void NetworkManager::disconnectFromServer ( void )
{

    // Deactivate the manager
    this->isActive = false;

    // Disconnect from the server
    this->tcpSocket.disconnectFromHost();

}

void NetworkManager::sendMessage ( const Message& message )
{

    MessageTransport messageTransport = message.getTransport();

    switch ( messageTransport )
    {

        case MessageTransport::TCP :
        {
            this->sendTcpMessage(message);
            break;
        }

        case MessageTransport::UDP :
        {
            this->sendUdpMessage(message);
            break;
        }

    }

}

void NetworkManager::initializeServerCredentials()
{

    // Initialize the settings object
    QSettings settings("PongOnlineClient.ini",QSettings::IniFormat);

    // Retrieve server address and port from the client settings
    QString serverAddressString = settings.value("Server/ServerAddress").toString();
    this->serverAddress = QHostAddress(serverAddressString);
    this->serverPort = settings.value("Server/ServerPort").toUInt();

}

void NetworkManager::sendUdpMessage ( const Message& message )
{

    // Send a message over a UDP socket
    QByteArray messageData { message.getData() };
    int messageSize { messageData.size() };
    qint64 bytesWritten
    {
        this->udpSocket.writeDatagram
        (
            messageData,
            this->serverAddress,
            this->serverPort
        )
    };

    // Flush data from the output buffer to the actual socket
    this->udpSocket.flush();

    // Check if the message was sent completely
    if ( messageSize != bytesWritten )
    {
        throw QException();
    }

}

void NetworkManager::sendTcpMessage ( const Message& message )
{

    // Send a message over the TCP socket
    QByteArray messageData;
    messageData.append(message.getData());
    messageData.append(Delimiter().getData());
    int messageSize { messageData.size() };
    qint64 bytesWritten { this->tcpSocket.write(messageData) };

    // Flush data from the output buffer to the actual socket
    this->tcpSocket.flush();

    // Check if the message was sent completely
    if ( messageSize != bytesWritten )
    {
        throw QException();
    }

}

void NetworkManager::initializeHandshakeTimer ( void )
{

    // The handshake message will be resent every "handshakeTimeout" seconds ...
    this->handshakeTimer.setInterval(NetworkManager::handshakeTimeout);

    // ... untill it gets a response
    this->handshakeTimer.setSingleShot(false);

    // Listen to the timer timeout signal
    QObject::connect
    (
        &this->handshakeTimer,
        SIGNAL(timeout()),
        this,
        SLOT(handshake())
    );

}

void NetworkManager::initializeUdpSocket ( void )
{

    // Process the UDP socket input
    QObject::connect
    (
        &this->udpSocket,
        SIGNAL(readyRead()),
        this,
        SLOT(processUdpInput())
    );

    // Bind the UDP socket to an arbitrary address
    this->udpSocket.bind();

}

void NetworkManager::initializeTcpSocket ( void )
{

    // Process the TCP socket input
    QObject::connect
    (
        &this->tcpSocket,
        SIGNAL(readyRead()),
        this,
        SLOT(processTcpInput())
    );

    // Process TCP socket state change
    QObject::connect
    (
        &this->tcpSocket,
        SIGNAL(stateChanged(QAbstractSocket::SocketState)),
        this,
        SLOT(processState(QAbstractSocket::SocketState))
    );

}

void NetworkManager::processState ( QAbstractSocket::SocketState state )
{

    if ( state == QAbstractSocket::UnconnectedState )
    {

        // Set connection state value
        this->isConnected = false;

        // Emit the corresponding signal
        emit this->disconnected();

        // Try to reconnect
        if ( this->isActive == true )
        {
            this->connectToServer();
        }

    }

}

void NetworkManager::handshake ( void )
{
    // Send a handshake message to the server
    HandshakeResponse handshakeResponse(this->tcpAddress,this->tcpPort);
    this->sendMessage(handshakeResponse);
}

void NetworkManager::processUdpInput ( void )
{

    // Receive the pending datagram
    QHostAddress senderAddress;
    quint16 senderPort;
    quint64 datagramSize = this->udpSocket.pendingDatagramSize();
    QByteArray datagram(datagramSize,0);
    char* datagramPtr = datagram.data();
    this->udpSocket.readDatagram(datagramPtr,datagramSize,&senderAddress,&senderPort);

    // Check if the datagram was sent by the server
    bool sentByServer
    {
        senderAddress == this->serverAddress
            &&
        senderPort == this->serverPort
    };

    // Ignore datagrams sent not from server
    if ( sentByServer == false )
    {
        return;
    }

    // If the connection is not established yet
    if ( this->isConnected == false )
    {

        // ... the only message which is processed is the handshake ack message
        HandshakeAck HandshakeAck(datagram);

        // The handshake ack was received
        // Stop the handshake timer
        this->handshakeTimer.stop();

        // Alter the connection state
        this->isConnected = true;

        // Emit the corresponding signal
        emit this->connected();

    }

    // If the connection is established already
    else
    {

        // Try to parse a message
        Message* messagePtr = MessageParser::parse(datagram,MessageTransport::UDP);

        // The message was parsed successfully
        if ( messagePtr != nullptr )
        {

            // Emit the message
            emit this->messageReceived(messagePtr);

        }

    }

}

void NetworkManager::processTcpInput ( void )
{

    // Retrieve all input data from the TCP socket
    QByteArray tcpInputData { this->tcpSocket.readAll() };

    // Append all input data to the TCP socket local buffer
    this->tcpSocketBuffer.append(tcpInputData);

    // Check if the data received is a complete message
    QByteArray messageDelimiter { Delimiter().getData() };
    bool messageReceived { this->tcpSocketBuffer.contains(messageDelimiter) };

    // The whole message is not received yet
    if ( messageReceived == false )
    {
        return;
    }

    // The whole message is already received
    // Extract the message
    int messageDelimiterIndex = this->tcpSocketBuffer.indexOf(messageDelimiter);
    QByteArray message = this->tcpSocketBuffer.left(messageDelimiterIndex);

    // Remove the message received with the delimiter
    this->tcpSocketBuffer.remove(0,messageDelimiterIndex+1);

    // When the connection is established manager does not care about TCP input
    if ( this->isConnected == true )
    {

        // Try to parse a message
        Message* messagePtr = MessageParser::parse(message,MessageTransport::TCP);

        // The message was parsed successfully
        if ( messagePtr != nullptr )
        {

            // Emit the message
            emit this->messageReceived(messagePtr);

        }

    }

    // When the connection is not established yet ...
    else
    {

        // ... the only message which is processed is the handshake message
        try
        {

            // Retrieve client't real address and port from the handshake message
            HandshakeRequest handshakeRequest(message);
            this->tcpAddress = handshakeRequest.getAddress();
            this->tcpPort = handshakeRequest.getPort();

            // Begin UDP handshake
            this->handshakeTimer.start();

        }

        catch ( ... )
        {

        }

    }

    // Check if there are some more messages available
    this->processTcpInput();

}
