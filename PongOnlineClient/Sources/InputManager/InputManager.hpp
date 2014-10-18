#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <QWidget>
#include <QTimer>
#include <MoveDirection/MoveDirection.hpp>

class InputManager :
    public QWidget
{
    Q_OBJECT
    public:
        explicit InputManager ( QWidget* parentPtr = nullptr );
    private:
        bool eventFilter ( QObject* targetPtr , QEvent* eventPtr );
        void initializeSamplingTimer ( void );
        QTimer samplingTimer;
        bool leftIsPressed;
        bool rightIsPressed;
    public slots:
        void enable ( void );
        void disable ( void );
    private slots:
        void sample ( void );
    signals:
        void sampled ( MoveDirection moveDirection );
};

#endif // INPUTMANAGER_HPP
