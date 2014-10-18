#include <InputManager/InputManager.hpp>
#include <QKeyEvent>

#include <QDebug>
InputManager::InputManager ( QWidget* parentPtr ) :
    QWidget(parentPtr),
    leftIsPressed(false),
    rightIsPressed(false)
{
    this->initializeSamplingTimer();
}

bool InputManager::eventFilter ( QObject* /* targetPtr */ , QEvent* eventPtr )
{

    // Catch the key press event...
    if ( eventPtr->type() == QEvent::KeyPress )
    {

        // Upcast the event pointer
        QKeyEvent* keyEventPtr = reinterpret_cast<QKeyEvent*>(eventPtr);

        // Check which key was pressed
        switch ( keyEventPtr->key() )
        {

            case Qt::Key_Left :
            {
                this->leftIsPressed = true;
                if ( this->rightIsPressed == true )
                {
                    this->rightIsPressed = false;
                }
                break;
            }

            case Qt::Key_Right :
            {
                this->rightIsPressed = true;
                if ( this->leftIsPressed == true )
                {
                    this->leftIsPressed = false;
                }
                break;
            }

            default :
            {
                break;
            }

        }

    }

    // ... and key release event
    else if ( eventPtr->type() == QEvent::KeyRelease )
    {

        // Upcast the event pointer
        QKeyEvent* keyEventPtr = reinterpret_cast<QKeyEvent*>(eventPtr);

        // Check which key was pressed
        switch ( keyEventPtr->key() )
        {

            case Qt::Key_Left :
            {
                this->leftIsPressed = false;
                break;
            }

            case Qt::Key_Right :
            {
                this->rightIsPressed = false;
                break;
            }

            default :
            {
                break;
            }

        }

    }

    // Propogate the event
    return false;

}

void InputManager::initializeSamplingTimer()
{
    this->samplingTimer.setSingleShot(false);
    this->samplingTimer.setInterval(50);
    QObject::connect
    (
        &this->samplingTimer,
        SIGNAL(timeout()),
        this,
        SLOT(sample())
    );
}

void InputManager::enable()
{
    this->samplingTimer.start();
}

void InputManager::disable()
{
    this->samplingTimer.stop();
}

void InputManager::sample ( void )
{

    MoveDirection moveDirection;

    // Left arrow is pressed
    if ( this->leftIsPressed )
    {

        moveDirection = MoveDirection::Left;

    }

    // Right arrow is pressed
    else if ( this->rightIsPressed )
    {

        moveDirection = MoveDirection::Right;

    }

    // Neither left nor right arrow is pressed
    else
    {

        moveDirection = MoveDirection::None;

    }

    emit this->sampled(moveDirection);

}

