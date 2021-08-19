#include <QtMath>
#include "smallcorona.h"
#include "bullet.h"
#include "spritemanager.h"

const int kSmallCoronaRadius = 30;
const int kSmallCoronaZValue = -1;
const int kAnimationInterval = 9;
const qreal kPulseFactor = 0.3;
const qreal kSpeedFactor = 0.1;
const int kSmallCoronaScore = 5;

SmallCorona::SmallCorona(QGraphicsView* graphics_area, int x, int y, qreal size, qreal speed) :
    Mob(graphics_area, GraphicsUnit::kSmallCorona, x, y, size * kSmallCoronaRadius, size * kSmallCoronaRadius),
    speed_(speed),
    animation_(new QGraphicsItemAnimation()),
    timeline_(new QTimeLine()),
    frame_counter_(0)
{
    paused_ = false;
    this->setZValue(kSmallCoronaZValue);
}

SmallCorona::~SmallCorona()
{
    graphics_area_->scene()->removeItem(this);
    timeline_->stop();
    delete animation_;
    delete timeline_;
}

QRectF SmallCorona::boundingRect() const
{
    return rect_;
}

void SmallCorona::SetPaused(bool paused)
{
    paused_ = paused;
}

void SmallCorona::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
   painter->drawImage(rect_, *SpriteManager::GetImage(SpriteManager::kSmallVirus));
}

void SmallCorona::Update(int drawer_x, int drawer_y) {
    if (!is_alive_ || paused_) {
        return;
    }
    QPointF direction_ = Utility::Normalize(drawer_x - x_, drawer_y - y_, speed_);
    x_ += direction_.x();
    y_ += direction_.y();
    setX(x_);
    setY(y_);

    this->setScale(1.0 + (frame_counter_ > kAnimationInterval ? 1 : 0) * kPulseFactor);

    this->update();
    HandleCollisions();
    frame_counter_ = (++frame_counter_) % (kAnimationInterval * 2);
}

void SmallCorona::SetItems()
{
    graphics_area_->scene()->addItem(this);
}

void SmallCorona::SetSpeed(int speed)
{
    speed_ = speed * kSpeedFactor;
}

void SmallCorona::HandleCollisions()
{
    for (auto item : this->collidingItems()) {
        GraphicsUnit* item_s = dynamic_cast<GraphicsUnit*>(item);
        if (item_s == nullptr) {
            continue;
        }
        switch(item_s->GetType()) {
            case GraphicsUnit::kBullet:
                 if (item_s->IsActive()) {
                     dynamic_cast<Bullet*>(item_s)->Die();
                     Die();
                 }
            break;
        case GraphicsUnit::kPin:
        case GraphicsUnit::kBigBoom:
        case GraphicsUnit::kBoom:
            if (Utility::Distance(item_s->x(), item_s->y(), this->x(), this->y()) <
                this->GetWidth() / 2 + item_s->GetWidth() / 2) {
                Die();
            }
            break;
        case GraphicsUnit::kSmallCorona:
            return;
        }
    }
}

void SmallCorona::Die()
{
    emit Scored(kSmallCoronaScore);
    is_alive_ = false;
    timeline_ = new QTimeLine(300);
    animation_ = new QGraphicsItemAnimation();
    animation_->setItem(this);
    animation_->setTimeLine(timeline_);
    animation_->setScaleAt(0, 1,1);
    animation_->setScaleAt(1, 0,0);

    timeline_->setEasingCurve(QEasingCurve::Linear);
    connect(timeline_, &QTimeLine::finished, this, [=] {
        delete this;});
    timeline_->start();
}
