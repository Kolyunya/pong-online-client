#ifndef GAME_HPP
#define GAME_HPP

#include <Game/GameBase/GameBase.hpp>
#include <FieldView/FieldView.hpp>
#include <ScoreView/ScoreView.hpp>
#include <InputManager/InputManager.hpp>

class QGraphicsView;

class QLabel;

class ScoreData;

class Game :
    public GameBase
{
    Q_OBJECT
    public:
        explicit Game ( void );
        void setViewport ( QGraphicsView* viewportPtr );
        void setScoreLabel ( QLabel* scoreLabelPtr );
    private:
        void configureFieldView ( void );
        void configureScoreView ( void );
        FieldView fieldView;
        ScoreView scoreView;
    signals:
        void fieldDataReceived ( FieldData* fieldDataPtr );
        void scoreDataReceived ( ScoreData* scoreDataPtr );
};

#endif // GAME_HPP
