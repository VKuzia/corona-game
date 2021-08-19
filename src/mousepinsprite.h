#ifndef MOUSEPINSPRITE_H
#define MOUSEPINSPRITE_H
#include "graphicsunit.h"
#include "coronabullet.h"

class MousePinSprite : public GraphicsUnit
{
    Q_OBJECT
public:
    MousePinSprite(QGraphicsView* graphics_area, int x, int y, qreal size);
    ~MousePinSprite() override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void Update(int x, int y);
private:
    friend class MousePin;
    int transparency_;
    void HandleCollisions();
};

#endif // MOUSEPINSPRITE_H
