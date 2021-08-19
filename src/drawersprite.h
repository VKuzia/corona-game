#ifndef DRAWERSPRITE_H
#define DRAWERSPRITE_H
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsView>
#include "graphicsunit.h"
#include "spritemanager.h"
class DrawerSprite : public GraphicsUnit
{
public:
    DrawerSprite(QObject* parent, int transparency, qreal size);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void Update(int x, int y);
private:
    int transparency_;
};

#endif // DRAWERSPRITE_H
