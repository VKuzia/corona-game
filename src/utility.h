#ifndef UTILITY_H
#define UTILITY_H
#include <QPointF>
#include <QtMath>
#include <QRandomGenerator>

class Utility
{
public:
    static qreal GetAngle(qreal x, qreal y);
    static qreal GetAngle(QPointF p);
    static qreal GetAngle(qreal x2, qreal y2, qreal x1, qreal y1);
    static qreal GetAngle(QPointF p2, QPointF p1);

    static QPointF Normalize(qreal x, qreal y, qreal modulo);
    static QPointF Normalize(qreal x2, qreal y2, qreal x1, qreal y1, qreal modulo);
    static QPointF Normalize(QPointF p2, QPointF p1, qreal modulo);

    static qreal Distance(QPointF p1, QPointF p2);
    static qreal Distance(int x1, int y1, int x2, int y2);

    static QRandomGenerator generator;
};

#endif // UTILITY_H
