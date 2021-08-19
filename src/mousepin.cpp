#include "mousepin.h"
#include <QtMath>
#include <QGraphicsBlurEffect>

const int kRadius = 90;
const int kDefaultSpriteNum = 3;

MousePin::MousePin(QGraphicsView *graphics_area, qreal size) :
    graphics_area_(graphics_area),
    sprites_(QVector<MousePinSprite*>()),
    x_(0),
    y_(0),
    radius_(kRadius),
    sprite_num_(kDefaultSpriteNum),
    first_update_(false),
    paused_(false),
    size_(size)
{

}

MousePin::~MousePin() {}

void MousePin::SetItems(qreal size)
{
    radius_ = kRadius * (size);
    for (int i = sprites_.size() - 1; i >= 0; i--) {
        delete sprites_.back();
        sprites_.pop_back();
    }
    for (int i = 0; i < sprite_num_; i++) {
      sprites_.push_back(new MousePinSprite(graphics_area_, 0, 0, size_));
    }
   Update(x_, y_, true);
    for (int i = 0; i < sprite_num_; i++) {
        graphics_area_->scene()->addItem(sprites_[i]);
    }
}

void MousePin::Update(int x, int y, bool set_items)
{
    if (paused_ && !set_items) {
        return;
    }
    qreal angle = 0;
    if (!first_update_) {
        first_update_ = true;
    } else {
        QPointF center = graphics_area_->mapToGlobal(QPoint(0,0));
        center.setX(center.rx() + x_ + graphics_area_->width() / 2);
        center.setY(center.ry() + y_ + graphics_area_->height() / 2);
        angle = qDegreesToRadians(180.0) + Utility::GetAngle(QCursor::pos(), center);
    }

    qreal dif = qDegreesToRadians(360.0 / sprite_num_);
    for (int i = 0; i < sprite_num_; i++) {
        sprites_[i]->Update(radius_ * qCos(angle) + x,
                            radius_ * qSin(angle) + y);
        sprites_[i]->setRotation(qRadiansToDegrees(angle));
        angle += dif;
        sprites_[i]->update();
        sprites_[i]->HandleCollisions();
    }
    x_ = x;
    y_ = y;
}

void MousePin::SetPaused(bool paused)
{
    paused_ = paused;
}

