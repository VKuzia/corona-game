#ifndef BULLET_H
#define BULLET_H
#include "graphicsunit.h"
#include "boom.h"

class Bullet : public GraphicsUnit
{
    Q_OBJECT
public:
    Bullet(QGraphicsView* graphics_area, int x, int y, qreal speed, qreal size);
    Bullet(QGraphicsView* graphics_area, int x, int y, qreal speed, int width, int height);
    virtual ~Bullet() override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    virtual void SetPaused(bool) override;
    virtual void Die();

    qreal x();
    qreal y();

protected:
    virtual void StartAnimation();
    qreal size_;
    qreal speed_;
    QPointF direction_;
    QGraphicsItemAnimation* animation_;
    QTimeLine* timeline_;


};

#endif // BULLET_H
