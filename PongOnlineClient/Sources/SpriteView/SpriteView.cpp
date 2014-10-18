#include <SpriteView/SpriteView.hpp>
#include <QPropertyAnimation>

const QPointF& SpriteView::getPosition ( void ) const
{
    return this->position;
}

void SpriteView::setPosition ( const QPointF& position )
{
    this->setOffset(position);
    this->position = position;
}

void SpriteView::moveTo ( const SpriteModel& model , quint32 duration )
{
    QRectF spriteRect = model.getRectangle();
    QPointF spritePosition = spriteRect.topLeft();
    this->moveTo(spritePosition,duration);
}

void SpriteView::moveTo ( const QPointF& position , quint32 duration )
{
    QPropertyAnimation* animation = new QPropertyAnimation(this,"position");
    animation->setStartValue(this->getPosition());
    animation->setEndValue(position);
    animation->setDuration(duration);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
