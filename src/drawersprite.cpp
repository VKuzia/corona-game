#include "drawersprite.h"
#include <QTextStream>




QRectF DrawerSprite::boundingRect() const
{
    return rect_;
}

void DrawerSprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->setBrush(QColor::fromRgb(0,150,20,transparency_));
//    painter->setPen(QColor::fromRgb(200,200,200,transparency_));
//    painter->drawEllipse(-width_ / 2, -height_ / 2, width_ , height_ );
    painter->setOpacity(transparency_ / 255.0);
    painter->drawImage(rect_, *SpriteManager::GetImage(SpriteManager::kBsu));
}

void DrawerSprite::Update(int x, int y)
{
    this->moveBy(x-x_, y-y_);
    this->update();
    x_ = x;
    y_ = y;
}
