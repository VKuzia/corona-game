#include "utility.h"
#include <QDateTime>

QRandomGenerator Utility::generator = QRandomGenerator(QDateTime::currentMSecsSinceEpoch() / 1000);

qreal Utility::GetAngle(qreal x, qreal y)
{
    qreal distance = qSqrt(x * x + y * y);
    if (qAbs(distance) < 0.0001) {
        return 0;
    }
    x /= distance;
    y /= distance;

    qreal angle = qAcos(x);
    if (y < 0) {
        angle =  qDegreesToRadians(360.0 - qRadiansToDegrees(angle));
    }
    return angle;
}

qreal Utility::GetAngle(QPointF p)
{
    return GetAngle(p.x(), p.y());
}

qreal Utility::GetAngle(qreal x2, qreal y2, qreal x1, qreal y1)
{
    return GetAngle(x2-x1, y2-y1);
}

qreal Utility::GetAngle(QPointF p2, QPointF p1)
{
    return GetAngle(p2.x() - p1.x(), p2.y() - p1.y());
}

QPointF Utility::Normalize(qreal x, qreal y, qreal modulo)
{
    qreal distance = qSqrt(x * x + y * y);
    if (distance < 0.0001) {
        return QPointF(0.0, 0.0);
    }
    qreal ratio = modulo / distance;
    return QPointF(x * ratio, y * ratio);

}

QPointF Utility::Normalize(qreal x2, qreal y2, qreal x1, qreal y1, qreal modulo)
{
    return Normalize(x2-x1, y2-y1, modulo);
}

QPointF Utility::Normalize(QPointF p2, QPointF p1, qreal modulo)
{
    return Normalize(p2.x() - p1.x(), p2.y() - p1.y(), modulo);
}

qreal Utility::Distance(QPointF p1, QPointF p2)
{
    return qSqrt((p1.x()-p2.x()) * (p1.x()-p2.x()) + (p1.y()-p2.y()) * (p1.y()-p2.y()));
}

qreal Utility::Distance(int x1, int y1, int x2, int y2)
{
    return Distance(QPointF(x1, y1), QPointF(x2, y2));
}

