#include <QtMath>
#include "bullet.h"
#include "utility.h"
#include "spritemanager.h"

const int kBulletWidth = 12;
const int kBulletHeight = 30;
const qreal kBulletBoomSize = 0.08;
const qreal kBulletBoomTime = 0.5;
const qreal kBulletOpacity = 0.75;
const qreal kBulletZValue = 1000;
const qreal kBulletDistance = 4000;
const qreal kBulletTime = 3000;

Bullet::Bullet(QGraphicsView* graphics_area, int x, int y, qreal speed, qreal size) :
    GraphicsUnit(graphics_area, GraphicsUnit::kBullet, x, y,
                 size * kBulletWidth, size * kBulletHeight),
    speed_(speed),
    animation_(new QGraphicsItemAnimation()),
    timeline_(new QTimeLine())
{
    this->setZValue(kBulletZValue);
    QPointF center = graphics_area_->mapToGlobal(QPoint(0,0));
    center.setX(center.rx() + x_ + graphics_area_->width() / 2);
    center.setY(center.ry() + y_ + graphics_area_->height() / 2);
    direction_ = Utility::Normalize(QCursor::pos(), center, kBulletDistance);
//    direction_ *= speed_;
    this->setOpacity(kBulletOpacity);
    setX(x_);
    setY(y_);
    this->setRotation(90 + qRadiansToDegrees(Utility::GetAngle(direction_)));

    StartAnimation();

    graphics_area_->scene()->addItem(this);
}


Bullet::Bullet(QGraphicsView *graphics_area, int x, int y, qreal speed, int width, int height) :
        GraphicsUnit(graphics_area, GraphicsUnit::kBullet, x, y, width, height),
        speed_(speed),
        animation_(new QGraphicsItemAnimation()),
        timeline_(new QTimeLine())
{
    this->setZValue(kBulletZValue);
}

Bullet::~Bullet()
{
    this->graphics_area_->scene()->removeItem(this);
    delete animation_;
    delete timeline_;
}

QRectF Bullet::boundingRect() const
{
    return rect_;
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawImage(rect_, *SpriteManager::GetImage(SpriteManager::kBlueBullet));
}

void Bullet::SetPaused(bool paused)
{
    paused_ = paused;
    timeline_->setPaused(paused_);
}

void Bullet::Die()
{
    new Boom(graphics_area_, GraphicsUnit::kBoom, this->x(), this->y(), kBulletBoomSize, kBulletBoomTime);
    is_active_ = false;
    timeline_->stop();
    timeline_ = new QTimeLine(200);
    animation_ = new QGraphicsItemAnimation();
    animation_->setItem(this);
    animation_->setTimeLine(timeline_);
    animation_->setScaleAt(0, 1,1);
    animation_->setScaleAt(1, 0.5, 0);
    timeline_->setEasingCurve(QEasingCurve::OutExpo);
    connect(timeline_, &QTimeLine::finished, this, [=] {
        delete this;
    });
    timeline_->start();
}

qreal Bullet::x()
{
    return dynamic_cast<QGraphicsItem*>(this)->x();
}

qreal Bullet::y()
{
    return dynamic_cast<QGraphicsItem*>(this)->y();
}

void Bullet::StartAnimation()
{
    if (speed_ < 0.01) {
        return;
    }
    timeline_ = new QTimeLine(kBulletTime / speed_);
    animation_ = new QGraphicsItemAnimation();
    animation_->setItem(this);
    animation_->setTimeLine(timeline_);
    animation_->setPosAt(0, QPointF(x_, y_));
    animation_->setPosAt(1, QPointF(x_ + direction_.x(), y_ + direction_.y()));
    timeline_->setEasingCurve(QEasingCurve::Linear);
    connect(timeline_, &QTimeLine::finished, this, [=] {
        Die();
    });
    timeline_->start();

}
