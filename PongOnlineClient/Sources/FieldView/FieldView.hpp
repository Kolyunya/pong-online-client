#ifndef FIELDVIEW_HPP
#define FIELDVIEW_HPP

#include <QObject>
#include <FieldModel/FieldModel.hpp>

class SpriteView;

class QGraphicsView;

class FieldView :
    public QObject
{
    Q_OBJECT
    public:
        void setModel ( FieldModel* modelPtr );
        void setViewport ( QGraphicsView* viewportPtr );
    private:
        void initializeScene ( void );
        void initializeBackground ( void );
        void initializeLayout ( void );
        void initializePlayer ( void );
        void initializeEnemy ( void );
        void initializeBall ( void );
        void updatePlayerPosition ( bool instantly = false );
        void updateEnemyPosition ( bool instantly = false );
        void updateBallPosition ( bool instantly = false );
        FieldModel* modelPtr;
        QGraphicsView* viewportPtr;
        SpriteView* playerSpritePtr;
        SpriteView* enemySpritePtr;
        SpriteView* ballSpritePtr;
        QPixmap* playerPixmapPtr;
        QPixmap* enemyPixmapPtr;
        QPixmap* ballPixmapPtr;
    public slots:
        void update ( void );
};

#endif // FIELDVIEW_HPP
