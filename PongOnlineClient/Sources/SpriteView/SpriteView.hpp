#ifndef SPRITEVIEW_HPP
#define SPRITEVIEW_HPP

#include <QObject>
#include <QPointF>
#include <QGraphicsPixmapItem>
#include <SpriteModel/SpriteModel.hpp>

class SpriteView :
    public QObject,
    public QGraphicsPixmapItem
{
    Q_OBJECT
        Q_PROPERTY(QPointF position READ getPosition  WRITE setPosition )
    public:
        const QPointF& getPosition ( void ) const;
        void setPosition ( const QPointF& position );
        void moveTo ( const SpriteModel& model , quint32 duration = 100 );
        void moveTo ( const QPointF& position , quint32 duration = 100 );
    private:
        QPointF position;
};

#endif // SPRITEVIEW_HPP
