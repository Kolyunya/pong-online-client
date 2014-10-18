#include <QPointF>
#include <StatusBar/StatusBarEasingCurve/StatusBarEasingCurve.hpp>

StatusBarEasingCurve::StatusBarEasingCurve ( void ) :
    QEasingCurve(QEasingCurve::BezierSpline)
{

    this->addCubicBezierSegment
    (
        QPointF(0.05,0.45),
        QPointF(0.05,0.45),
        QPointF(0.50,0.50)
    );

    this->addCubicBezierSegment
    (
        QPointF(0.55,0.95),
        QPointF(0.55,0.95),
        QPointF(1,1)
    );

}
