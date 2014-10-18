#include <Game/Game.hpp>

Game::Game ( void )
{
    this->configureFieldView();
    this->configureScoreView();
    this->score.setLimit(42);
}

void Game::setViewport ( QGraphicsView* viewportPtr )
{
    this->fieldView.setViewport(viewportPtr);
}

void Game::setScoreLabel ( QLabel* scoreLabelPtr )
{
    this->scoreView.setLabel(scoreLabelPtr);
}

void Game::configureFieldView ( void )
{

    this->fieldView.setModel(&this->field);

    QObject::connect
    (
        this,
        SIGNAL(fieldDataReceived(FieldData*)),
        &this->field,
        SLOT(update(FieldData*))
    );


    QObject::connect
    (
        this,
        SIGNAL(scoreDataReceived(ScoreData*)),
        &this->score,
        SLOT(set(ScoreData*))
    );

    QObject::connect
    (
        &this->field,
        SIGNAL(updated()),
        &this->fieldView,
        SLOT(update())
    );

}

void Game::configureScoreView()
{

    this->scoreView.setModel(&this->score);

    QObject::connect
    (
        this,
        SIGNAL(scoreChanged()),
        &this->scoreView,
        SLOT(update())
    );

}
