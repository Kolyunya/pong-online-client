#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QtWidgets/QApplication>
#include <Windows/Main/WindowMain.hpp>
#include <NetworkManager/NetworkManager.hpp>
#include <InputManager/InputManager.hpp>
#include <MoveDirection/MoveDirection.hpp>

class ScoreData;

class Client :
    public QApplication
{
    Q_OBJECT
    friend class ClientStateUnconnected;
    public:
        Client ( int& argc , char** argv );
    private:
        void initializeInterface ( void );
        void initializeNetworkManager ( void );
        void initializeInputManager ( void );
        WindowMain interface;
        NetworkManager networkManager;
        InputManager inputManager;
    private slots:
        void exitGame ( void );
        void startGame ( void );
        void move ( MoveDirection moveDirection );
        void processMessage ( Message* messagePtr );
    signals:
        void gameStarted ( void );
        void gameEnded ( void );
        void fieldDataReceived ( FieldData* );
        void scoreDataReceived ( ScoreData* );
};

#endif // CLIENT_HPP
