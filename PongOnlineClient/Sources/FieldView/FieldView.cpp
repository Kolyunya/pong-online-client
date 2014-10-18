#include <QGraphicsView>
#include <QPropertyAnimation>
#include <FieldView/FieldView.hpp>
#include <SpriteView/SpriteView.hpp>

void FieldView::setModel ( FieldModel* modelPtr )
{
    this->modelPtr = modelPtr;
}

void FieldView::setViewport ( QGraphicsView* graphicsViewPtr )
{
    this->viewportPtr = graphicsViewPtr;
    this->initializeScene();
    this->initializeBackground();
    this->initializePlayer();
    this->initializeEnemy();
    this->initializeBall();
}

void FieldView::initializeScene ( void )
{
    QGraphicsScene* graphicsScenePtr = new QGraphicsScene(this);
    QRectF graphicsSceneRect = this->viewportPtr->sceneRect();
    graphicsScenePtr->setSceneRect(graphicsSceneRect);
    this->viewportPtr->setScene(graphicsScenePtr);
}

void FieldView::initializeBackground()
{
    QColor backgroundColor(0xF0,0xF0,0xF0);
    QBrush backgroundBrush(backgroundColor);
    QPen backgroundPen(Qt::NoPen);
    qreal backgroundWidth = this->viewportPtr->sceneRect().width();
    qreal backgroundHeight = this->viewportPtr->sceneRect().height();
    this->viewportPtr->scene()->addRect
    (
        0,
        0,
        backgroundWidth,
        backgroundHeight,
        backgroundPen,
        backgroundBrush
    );
}

void FieldView::initializeLayout ( void )
{
    QColor layoutColor(0x00,0x00,0x42);
    QBrush backgroundBrush(Qt::NoBrush);
    QPen backgroundPen(layoutColor);
    backgroundPen.setWidth(5);
    this->viewportPtr->scene()->addEllipse
    (
        0,
        0,
        150,
        150,
        backgroundPen,
        backgroundBrush
    );
}

void FieldView::initializePlayer ( void )
{
    this->playerPixmapPtr = new QPixmap(":/Graphics/PlayerPlatform.png");
    this->playerSpritePtr = new SpriteView();
    this->playerSpritePtr->setPixmap(*this->playerPixmapPtr);
    this->viewportPtr->scene()->addItem(this->playerSpritePtr);
    this->updatePlayerPosition(true);
}

void FieldView::initializeEnemy()
{
    this->enemyPixmapPtr = new QPixmap(":/Graphics/EnemyPlatform.png");
    this->enemySpritePtr = new SpriteView();
    this->enemySpritePtr->setPixmap(*this->enemyPixmapPtr);
    this->viewportPtr->scene()->addItem(this->enemySpritePtr);
    this->updateEnemyPosition(true);
}

void FieldView::initializeBall()
{
    this->ballPixmapPtr = new QPixmap(":/Graphics/Ball.png");
    this->ballSpritePtr = new SpriteView();
    this->ballSpritePtr->setPixmap(*this->ballPixmapPtr);
    this->viewportPtr->scene()->addItem(this->ballSpritePtr);
    this->updateBallPosition(true);
}

void FieldView::updatePlayerPosition ( bool instantly )
{
    const SpriteModel& player = this->modelPtr->getPlayer(0);
    const quint32 animationDuration = instantly ? 0 : 100;
    this->playerSpritePtr->moveTo(player,animationDuration);
}

void FieldView::updateEnemyPosition ( bool instantly )
{
    const SpriteModel& enemy = this->modelPtr->getPlayer(1);
    const quint32 animationDuration = instantly ? 0 : 100;
    this->enemySpritePtr->moveTo(enemy,animationDuration);
}

void FieldView::updateBallPosition ( bool instantly )
{
    const SpriteModel& ball = this->modelPtr->getBall();
    const quint32 animationDuration = instantly ? 0 : 100;
    this->ballSpritePtr->moveTo(ball,animationDuration);
}

void FieldView::update()
{
    this->updatePlayerPosition();
    this->updateEnemyPosition();
    this->updateBallPosition();
}
