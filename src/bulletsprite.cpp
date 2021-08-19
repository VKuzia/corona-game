#include "bulletsprite.h"

BulletSprite::BulletSprite(QObject* parent, int x, int y, qreal size, int transparency) :
    GraphicsUnit(), size_(size),transparency_(transparency)
{
//     parent_ = parent;
//     width_ = (size_ * 12);
//     height_= (size_ * 24);
//     type_ = (GraphicsSprite::kBullet);
//     rect_ = QRectF(- width_ / 2,  - height_ / 2, width_, height_);

//     QTimeLine* timeline_ = new QTimeLine(2000);
//     QGraphicsItemAnimation *animation_ = new QGraphicsItemAnimation();
//     animation_->setItem(this);
//     animation_->setTimeLine(timeline_);
//     animation_->setPosAt(0, QPointF(x_, y_));
//     animation_->setPosAt(1, QPointF(x_ + 100, y_ + 100));
//     timeline_->setEasingCurve(QEasingCurve::Linear);
//     QObject::connect(timeline_, &QTimeLine::stop, this, [=] {
//         delete this;
//     });
//     timeline_->start();
}

BulletSprite::~BulletSprite()
{

}

QRectF BulletSprite::boundingRect() const
{
    return rect_;
}

void BulletSprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//        painter->setBrush(QColor::fromRgb(252, 140, 3, transparency_));
//        painter->setPen(QColor::fromRgb(255,255,255,0));
//        painter->drawEllipse(- width_ / 2,  - height_ / 2, width_, height_);
       painter->drawImage(rect_, *SpriteManager::GetImage(SpriteManager::kBlueBullet));
}

void BulletSprite::Update(int x, int y)
{
    moveBy(x-x_, y-y_);
    update();
    x_ = x;
    y_ = y;
}
