#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QTcpSocket>
#include <QTimer>
#include <Message/MessageTransport/MessageTransport.hpp>

class Message;

class NetworkManager :
    public QObject
{
    Q_OBJECT
    public:
        explicit NetworkManager ( QObject* parentPtr = nullptr );
        virtual ~NetworkManager ( void ) noexcept;
        bool getConnectionState ( void ) const;
        void connectToServer ( void );
        void disconnectFromServer ( void );
        void sendMessage ( const Message& message );
    private:
        void initializeServerCredentials ( void );
        void initializeHandshakeTimer ( void );
        void initializeUdpSocket ( void );
        void initializeTcpSocket ( void );
        void sendUdpMessage ( const Message& message );
        void sendTcpMessage ( const Message& message );
        QUdpSocket udpSocket;
        QTcpSocket tcpSocket;
        QHostAddress tcpAddress;
        quint16 tcpPort;
        QHostAddress serverAddress;
        quint16 serverPort;
        QByteArray tcpSocketBuffer;
        QTimer handshakeTimer;
        bool isActive;
        bool isConnected;
        static const unsigned int handshakeTimeout { 5000 };
        //static const unsigned int handshakeTimeout { 1000 };
    private slots:
        void handshake ( void );
        void processUdpInput ( void );
        void processTcpInput ( void );
        void processState ( QAbstractSocket::SocketState state );
    signals:
        void connected ( void );
        void disconnected ( void );
        void messageReceived ( Message* message );
};

#endif // NETWORKMANAGER_HPP
