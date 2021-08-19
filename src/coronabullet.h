#ifndef CORONABULLET_H
#define CORONABULLET_H
#include "bullet.h"

class CoronaBullet : public Bullet
{
public:
    CoronaBullet(QGraphicsView* graphics_area, int x, int y, int drawer_x, int drawer_y, qreal speed, qreal size);
    ~CoronaBullet() override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void Die() override;
    void StartAnimation() override;

};

#endif // CORONABULLET_H
