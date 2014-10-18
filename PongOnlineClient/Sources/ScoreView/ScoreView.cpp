#include <QLabel>
#include <QString>
#include <Game/GameScore/GameScore.hpp>
#include <ScoreView/ScoreView.hpp>

ScoreView::ScoreView(QObject *parent) :
    QObject(parent)
{
}

void ScoreView::setModel(GameScore *modelPtr)
{
    this->modelPtr = modelPtr;
}

void ScoreView::setLabel ( QLabel* labelPtr )
{
    this->labelPtr = labelPtr;
}

void ScoreView::update()
{
    QString playerScore = QString::number(this->modelPtr->getValue(0));
    QString enemyScore = QString::number(this->modelPtr->getValue(1));
    QString score = playerScore + " / " + enemyScore;
    this->labelPtr->setText(score);
}
