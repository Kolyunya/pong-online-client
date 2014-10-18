#include <QTimer>
#include <Windows/Main/WindowMain.hpp>
#include <Pages/MainMenu/PageMainMenu.hpp>
#include <Pages/Game/PageGame.hpp>
#include <Pages/Loading/Loading.hpp>

WindowMain::WindowMain ( QWidget* parentPtr ) :
    QMainWindow(parentPtr),
    uiPtr(nullptr),
    pagePtr(nullptr)
{
    this->initializeUi();
}

WindowMain::~WindowMain ( void )
{
    this->uninitializeUi();
}

void WindowMain::setPage ( QWidget* pagePtr )
{
    if ( this->pagePtr != nullptr )
    {
        this->uiPtr->Centralwidget->layout()->removeWidget(pagePtr);
        delete this->pagePtr;
    }
    this->uiPtr->Centralwidget->layout()->addWidget(pagePtr);
    this->pagePtr = pagePtr;
}

void WindowMain::initializeUi ( void )
{

    this->uiPtr = new Ui::WindowMain();
    this->uiPtr->setupUi(this);
    this->disconnected();

    // Main menu "Play" button
    QObject::connect
    (
        this->uiPtr->buttonPlay,
        SIGNAL(triggered()),
        this,
        SLOT(startGameClicked())
    );

    // Main menu "Settings" button
    QObject::connect
    (
        this->uiPtr->buttonSettings,
        SIGNAL(triggered()),
        this,
        SIGNAL(showSettings())
    );

    // Main menu "Exit" button
    QObject::connect
    (
        this->uiPtr->buttonExit,
        SIGNAL(triggered()),
        this,
        SIGNAL(exitGame())
    );

}

void WindowMain::uninitializeUi ( void )
{
    delete this->uiPtr;
    this->uiPtr = nullptr;
}

void WindowMain::connected ( void )
{

    this->uiPtr->buttonPlay->setEnabled(true);
    this->uiPtr->buttonSettings->setEnabled(false);
    this->uiPtr->buttonExit->setEnabled(true);

    QWidget* page = new PageMainMenu();

    QObject::connect
    (
        page,
        SIGNAL(startGame()),
        this,
        SLOT(startGameClicked())
    );

    this->setPage(page);

}

void WindowMain::disconnected ( void )
{
    this->uiPtr->buttonPlay->setEnabled(false);
    this->uiPtr->buttonSettings->setEnabled(false);
    this->uiPtr->buttonExit->setEnabled(true);
    Loading* pagePtr = new Loading();
    pagePtr->setText("Establishing connection...");
    this->setPage(pagePtr);
}

void WindowMain::gameStarted ( void )
{

    this->uiPtr->buttonPlay->setEnabled(false);
    this->uiPtr->buttonSettings->setEnabled(false);
    this->uiPtr->buttonExit->setEnabled(true);

    // Creage a game page
    PageGame* pageGamePtr = new PageGame();

    QObject::connect
    (
        this,
        SIGNAL(fieldDataReceived(FieldData*)),
        pageGamePtr,
        SIGNAL(fieldDataReceived(FieldData*))
    );

    QObject::connect
    (
        this,
        SIGNAL(scoreDataReceived(ScoreData*)),
        pageGamePtr,
        SIGNAL(scoreChanged(ScoreData*))
    );

    QObject::connect
    (
        this,
        SIGNAL(gameEnded()),
        pageGamePtr,
        SLOT(animateGameEnd())
    );

    QObject::connect
    (
        pageGamePtr,
        SIGNAL(gameEndAnimatied()),
        this,
        SLOT(connected())
    );

    // Show the game page
    this->setPage(pageGamePtr);

}

void WindowMain::startGameClicked ( void )
{
    this->uiPtr->buttonPlay->setEnabled(false);
    this->uiPtr->buttonSettings->setEnabled(false);
    this->uiPtr->buttonExit->setEnabled(true);
    Loading* pagePtr = new Loading();
    pagePtr->setText("Waiting for opponent...");
    this->setPage(pagePtr);
    QTimer::singleShot(5000,this,SIGNAL(startGame()));
}
