#ifndef STATUSBARWIDGET_HPP
#define STATUSBARWIDGET_HPP

#include <QLabel>
#include <QQueue>
#include <QString>
#include <QRectF>
#include <QFont>

class QPropertyAnimation;

class StatusBarWidget :
    public QLabel
{
    Q_OBJECT
    public:
        explicit StatusBarWidget ( QWidget* parent = nullptr );
        void setSceneRectangle ( const QRectF& rectangle );
        void setStatus ( const QString& status , quint32 duration );
        QSize sizeHint ( void ) const override;
    private:
        void configure ( void );
        QFont getFont ( void );
        QRectF getStartPosition ( void );
        QRectF getEndPosition ( void );
        QQueue<QPropertyAnimation*> animationQueue;
        QQueue<QString> statusQueue;
        QRectF sceneRectangle;
    private slots:
        void animate ( void );
        void moveQueue ( void );
        void processQueue ( void );
    signals:
        void complete ( void );
};

#endif // STATUSBARWIDGET_HPP
