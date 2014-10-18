#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include <QtWidgets/QMainWindow>
#include <ui_WindowMain.h>
#include <MoveDirection/MoveDirection.hpp>

class FieldData;

class ScoreData;

class WindowMain :
    public QMainWindow
{
    Q_OBJECT
    public:
        explicit WindowMain ( QWidget* parent = nullptr );
        virtual ~WindowMain();
    private:
        void setPage ( QWidget* pagePtr );
        void initializeUi ( void );
        void uninitializeUi ( void );
        Ui::WindowMain* uiPtr;
        QWidget* pagePtr;
    public slots:
        void connected ( void );
        void disconnected ( void );
        void gameStarted ( void );
    private slots:
        void startGameClicked ( void );
    signals:
        void startGame ( void );
        void exitGame ( void );
        void gameEnded ( void );
        void showSettings ( void );
        void move ( MoveDirection moveDirection );
        void fieldDataReceived ( FieldData* );
        void scoreDataReceived ( ScoreData* );
};

#endif // WINDOWMAIN_H
