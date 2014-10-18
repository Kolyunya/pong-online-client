#ifndef PAGEGAME_H
#define PAGEGAME_H

#include <QWidget>
#include <QString>
#include <QGraphicsScene>
#include <Game/Game.hpp>
#include <MoveDirection/MoveDirection.hpp>
#include <StatusBar/StatusBarWidget/StatusBarWidget.hpp>

class FieldData;

class QSound;

class QPropertyAnimation;

namespace Ui
{
    class PageGame;
}

class PageGame :
    public QWidget
{
    Q_OBJECT
    public:
        explicit PageGame ( QWidget* parentPtr = nullptr );
        ~PageGame ( void );
    private:
        void initializeInterface ( void );
        void initializeMusic ( void );
        void initializeGame ( void );
        void initializeStatusBar ( void );
        Ui::PageGame* ui;
        Game game;
        QSound* music;
        StatusBarWidget statusBar;
        static const quint32 afterGoalPause;
    private slots:
        void animateGetReady ( void );
        void animateScoreChange ( ScoreData* scoreData );
        void animateGameEnd ( void );
    signals:
        void fieldDataReceived ( FieldData* fieldDataPtr );
        void scoreChanged ( ScoreData* scoreDataPtr );
        void gameEndAnimatied ( void );
};

#endif // PAGEGAME_H
