#ifndef BULLETSPRITE_H
#define BULLETSPRITE_H
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include "graphicsunit.h"
#include "utility.h"
#include "spritemanager.h"

class BulletSprite : public GraphicsUnit
{
public:
    BulletSprite(QObject* parent, int x, int y, qreal size, int transparency);
    ~BulletSprite() override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void Update(int x, int y);
private:
    qreal size_;
    int transparency_;
};

#endif // BULLETSPRITE_H
