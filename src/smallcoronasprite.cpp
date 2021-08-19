#include "smallcoronasprite.h"
#include <QPainter>

SmallCoronaSprite::SmallCoronaSprite(QObject* parent, int x, int y, int width, int height, int transparency) :
    GraphicsUnit(parent, GraphicsUnit::kSmallCorona, x, y, width, height), transparency_(transparency)
{
    rect_ = QRectF(-width_/2, -height / 2, width_, height_);
}

SmallCoronaSprite::~SmallCoronaSprite()
{
//    delete image_;
}

QRectF SmallCoronaSprite::boundingRect() const
{
    return rect_;
}

void SmallCoronaSprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->setBrush(QColor::fromRgb(250, 10, 10, 230));
//    painter->drawPolygon(polygon_);
//    painter->setOpacity(transparency_ / 255.0);
    painter->drawImage(rect_, *SpriteManager::GetImage(SpriteManager::kSmallVirus));
}

void SmallCoronaSprite::Update(int x, int y)
{
    if (x == x_ && y == y_) {
        return;
    }
    moveBy(x-x_, y-y_);
    x_ = x;
    y_ = y;
    update();
}

int SmallCoronaSprite::GetType() const
{
    return type_;
}
