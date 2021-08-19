#ifndef SMALLCORONASPRITE_H
#define SMALLCORONASPRITE_H
#include "graphicsunit.h"
#include "spritemanager.h"
class SmallCoronaSprite : public GraphicsUnit
{
public:
    SmallCoronaSprite(QObject* parent, int x, int y, int width_, int height_, int transparency);
    ~SmallCoronaSprite();
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void Update(int x, int y);
    int GetType() const;

private:
    int transparency_;
};

#endif // SMALLCORONASPRITE_H
