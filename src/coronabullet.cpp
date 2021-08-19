#include "coronabullet.h"
#include "utility.h"
#include <QTextStream>

const int kCoronaBulletWidth = 12;
const int kCoronaBulletHeight = 30;
const qreal kCoronaBulletOpacity = 0.75;
const qreal kCoronaBulletDistance = 700;
const qreal kCoronaBulletTime = 1000;

CoronaBullet::CoronaBullet(QGraphicsView *graphics_area, int x, int y, int drawer_x, int drawer_y,
                           qreal speed, qreal size) :
    Bullet(graphics_area, x, y, speed, size * kCoronaBulletWidth, size * kCoronaBulletHeight) {
    if (Utility::Distance(drawer_x, drawer_y, x, y) < 1) {
        drawer_x += 5;
    }
    type_ = GraphicsUnit::kCoronaBullet;
    QTextStream out(stdout);
    direction_ = Utility::Normalize(drawer_x, drawer_y, x_, y_, kCoronaBulletDistance);
    this->setOpacity(kCoronaBulletOpacity);

    this->setRotation(90 + qRadiansToDegrees(Utility::GetAngle(direction_)));

    StartAnimation();

    graphics_area_->scene()->addItem(this);
}

CoronaBullet::~CoronaBullet()
{
//    timeline_->stop();
//    this->graphics_area_->scene()->removeItem(this);
//    delete animation_;
//    delete timeline_;
}

QRectF CoronaBullet::boundingRect() const
{
    return rect_;
}

void CoronaBullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawImage(rect_, *SpriteManager::GetImage(SpriteManager::kRedBullet));
}

void CoronaBullet::Die()
{
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
        this->setVisible(false);
        delete this;
    });
    timeline_->start();
}

void CoronaBullet::StartAnimation()
{
    if (speed_ < 0.01) {
        return;
    }
    timeline_ = new QTimeLine(kCoronaBulletTime / speed_);
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
