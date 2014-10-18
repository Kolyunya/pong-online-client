#include <QLayout>
#include <QtMultimedia/QSound>
#include <QPropertyAnimation>
#include <ui_PageGame.h>
#include <Pages/Game/PageGame.hpp>

const quint32 PageGame::afterGoalPause = 5000;

PageGame::PageGame ( QWidget* parentPtr ) :
    QWidget(parentPtr),
    ui(new Ui::PageGame),
    music(new QSound(":/Sounds/Music_001.wav"))
{
    this->initializeInterface();
    this->initializeMusic();
    this->initializeGame();
    this->initializeStatusBar();
    this->animateGetReady();
}

PageGame::~PageGame ( void )
{
    delete this->ui;
    delete this->music;
}

void PageGame::initializeInterface ( void )
{

    // Show interface
    this->ui->setupUi(this);

}

void PageGame::initializeMusic ( void )
{
    //this->music->play();
}

void PageGame::initializeGame ( void )
{

    this->game.setViewport(this->ui->graphicsView);
    this->game.setScoreLabel(this->ui->scorePanel);

    QObject::connect
    (
        this,
        SIGNAL(fieldDataReceived(FieldData*)),
        &this->game,
        SIGNAL(fieldDataReceived(FieldData*))
    );

    QObject::connect
    (
        this,
        SIGNAL(scoreChanged(ScoreData*)),
        &this->game,
        SIGNAL(scoreDataReceived(ScoreData*))
    );

    QObject::connect
    (
        this,
        SIGNAL(scoreChanged(ScoreData*)),
        this,
        SLOT(animateScoreChange(ScoreData*))
    );

}

void PageGame::initializeStatusBar ( void )
{
    this->statusBar.setParent(this);
    this->statusBar.setSceneRectangle(this->ui->graphicsView->sceneRect());
    this->statusBar.show();
}

void PageGame::animateGetReady ( void )
{
    QString text = "GET READY";
    quint64 duration = PageGame::afterGoalPause;
    this->statusBar.setStatus(text,duration);
}

void PageGame::animateScoreChange ( ScoreData* scoreData )
{
    QString text = this->ui->scorePanel->text();
    quint64 duration = PageGame::afterGoalPause;
    this->statusBar.setStatus(text,duration);
}

void PageGame::animateGameEnd ( void )
{
    QString text = "GAME OVER";
    quint64 duration = PageGame::afterGoalPause;
    this->statusBar.setStatus(text,duration);
    QObject::connect
    (
        &this->statusBar,
        SIGNAL(complete()),
        this,
        SIGNAL(gameEndAnimatied())
    );
}
