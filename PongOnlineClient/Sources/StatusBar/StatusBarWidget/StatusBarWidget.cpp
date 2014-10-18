#include <QLayout>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <StatusBar/StatusBarEasingCurve/StatusBarEasingCurve.hpp>
#include <StatusBar/StatusBarWidget/StatusBarWidget.hpp>


#include <QDebug>

StatusBarWidget::StatusBarWidget ( QWidget* parent ) :
    QLabel(parent)
{
    this->configure();
}

void StatusBarWidget::setSceneRectangle ( const QRectF& rectangle )
{
    this->sceneRectangle = rectangle;
}

void StatusBarWidget::setStatus ( const QString& status , quint32 duration )
{

     //  Add status text to the queue
    this->statusQueue.append(status);

    //  Add animation to the queue
    QPropertyAnimation* animation = new QPropertyAnimation
    (
        this,
        "geometry"
    );
    animation->setDuration(duration);
    animation->setStartValue(this->getStartPosition());
    animation->setEndValue(this->getEndPosition());
    animation->setEasingCurve(StatusBarEasingCurve());
    this->animationQueue.append(animation);

    QObject::connect
    (
        animation,
        SIGNAL(finished()),
        this,
        SLOT(processQueue())
    );

    //  The animation is first in the queue...
    if ( this->animationQueue.size() == 1 )
    {

        //  And should be started manually
        this->animate();

    }

}

QSize StatusBarWidget::sizeHint ( void ) const
{
    return QSize(400,200);
}

void StatusBarWidget::configure ( void )
{
    this->setFont(this->getFont());
    this->setAlignment(Qt::AlignCenter);
    this->setGeometry(0,0,400,200);

    // Add a shadow to the text
    QGraphicsDropShadowEffect* shadowPtr = new QGraphicsDropShadowEffect();
    shadowPtr->setBlurRadius(10);
    shadowPtr->setOffset(2,2);
    this->setGraphicsEffect(shadowPtr);

}

QFont StatusBarWidget::getFont ( void )
{
    QFont labelFont;
    labelFont.setBold(true);
    labelFont.setItalic(true);
    labelFont.setPointSize(25);
    labelFont.setFamily("Agency FB");
    return labelFont;
}

QRectF StatusBarWidget::getStartPosition ( void )
{
    QRectF labelRectangle = this->rect();
    qreal labelLeft = sceneRectangle.width() + this->rect().width() * 0.5;
    qreal labelTop = this->sceneRectangle.height() / 2 - labelRectangle.height() / 2;
    labelRectangle.moveTop(labelTop);
    labelRectangle.moveLeft(labelLeft);
    return labelRectangle;
}

QRectF StatusBarWidget::getEndPosition ( void )
{
    QRectF labelRectangle = this->rect();
    qreal labelLeft = -this->rect().width() * 1.5;
    qreal labelTop = this->sceneRectangle.height() / 2 - labelRectangle.height() / 2;
    labelRectangle.moveTop(labelTop);
    labelRectangle.moveLeft(labelLeft);
    return labelRectangle;
}

void StatusBarWidget::animate ( void )
{
    if ( this->animationQueue.isEmpty() )
    {
        emit this->complete();
        return;
    }
    this->setText(this->statusQueue.front());
    this->animationQueue.first()->start(QAbstractAnimation::DeleteWhenStopped);
}

void StatusBarWidget::moveQueue ( void )
{
    this->statusQueue.removeFirst();
    this->animationQueue.removeFirst();
}

void StatusBarWidget::processQueue ( void )
{
    this->moveQueue();
    this->animate();
}
