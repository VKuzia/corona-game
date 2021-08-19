#include <QtMath>
#include "bigcorona.h"
#include "bullet.h"
#include "coronabullet.h"
#include "spritemanager.h"

const int kBigCoronaWidth = 60;
const int kBigCoronaHeight = 60;

const int kBigCoronaZValue = -2;
const int kAnimationInterval = 15;
const qreal kPulseFactor = 0.23;
const qreal kSpeedFactor = 0.03;
const int kBigCoronaScore = 12;
const int kHitFrames = 4;
const int kLives = 3;
const int kShootInterval = 3250;
const QColor kColors[] = { QColor::fromRgb(134, 201, 18),
                           QColor::fromRgb(242, 255, 0),
                           QColor::fromRgb(255, 153, 0),
                           QColor::fromRgb(255, 38, 0)};

BigCorona::BigCorona(QGraphicsView* graphics_area, int x, int y, qreal size, qreal speed) :
    Mob(graphics_area, GraphicsUnit::kBigCorona, x, y, size * kBigCoronaWidth, size * kBigCoronaHeight),
    speed_(speed),
    animation_(new QGraphicsItemAnimation()),
    timeline_(new QTimeLine()),
    timer_(new QTimer()),
    frame_counter_(0),
    lives_(kLives),
    last_pin_(nullptr),
    effect_(new QGraphicsColorizeEffect()),
    animation_frame_(0),
    remaining_(0),
    time_to_shoot_(false)
{
    paused_ = false;
    this->setZValue(kBigCoronaZValue);
    effect_->setColor(kColors[lives_]);
    effect_->setStrength(0.7);
    this->setGraphicsEffect(effect_);

    connect(timer_, &QTimer::timeout, this, [=] {
        this->time_to_shoot_ = true;
    });
    timer_->start(kShootInterval);
}

BigCorona::~BigCorona()
{
    graphics_area_->scene()->removeItem(this);
    timeline_->stop();
    timer_->stop();
    delete timer_;
    delete animation_;
    delete timeline_;
}

QRectF BigCorona::boundingRect() const
{
    return rect_;
}

void BigCorona::SetPaused(bool paused)
{
    paused_ = paused;
    if (paused) {
       remaining_ = timer_->remainingTime();
       timer_->stop();
       timer_->setInterval(remaining_);
    } else {
        timer_->start();
    }
}

void BigCorona::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    if (animation_frame_ >= 1 && animation_frame_ <=kHitFrames) {
        effect_->setColor(QColor::fromRgb(57, 163, 0));
        animation_frame_++;
    } else if (animation_frame_ == kHitFrames + 1) {
        effect_->setColor(kColors[lives_]);
        animation_frame_ = 0;
    }
    painter->drawImage(rect_, *SpriteManager::GetImage(SpriteManager::kBigVirus));
}

void BigCorona::Shoot(int drawer_x, int drawer_y) const
{
    new CoronaBullet(graphics_area_, this->x(), this->y(), drawer_x, drawer_y, 0.3, 1);
}

void BigCorona::Update(int drawer_x, int drawer_y) {
    if (!is_alive_ || paused_) {
        return;
    }
    if (time_to_shoot_) {
        time_to_shoot_ = false;
        Shoot(drawer_x, drawer_y);
    }
    QPointF direction_ = Utility::Normalize(drawer_x - x_, drawer_y - y_, speed_);
    x_ += direction_.x();
    y_ += direction_.y();
    qreal angle = Utility::GetAngle(direction_);
    this->setRotation(qRadiansToDegrees(angle));
    setX(x_);
    setY(y_);

    this->setScale(1.0 + (frame_counter_ > kAnimationInterval ? 1 : 0) * kPulseFactor);

    this->update();
    HandleCollisions();
    frame_counter_ += 1;
    frame_counter_ = (frame_counter_) % (kAnimationInterval * 2);
}

void BigCorona::SetItems()
{
    graphics_area_->scene()->addItem(this);
}

void BigCorona::SetSpeed(int speed)
{
    speed_ = speed * kSpeedFactor;
}

void BigCorona::HandleCollisions()
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
                     Hit();
                 }
            break;
        case GraphicsUnit::kPin:
            if (item_s == last_pin_) {
                break;
            } else {
                last_pin_ = item_s;
                Hit();
                break;
            }

        case GraphicsUnit::kBigBoom:
            if (Utility::Distance(item_s->x(), item_s->y(), this->x(), this->y()) <
                this->GetWidth() / 2 + item_s->GetWidth() / 2) {
                Die();
           }
            break;
        case GraphicsUnit::kBoom:
            break;
        case GraphicsUnit::kSmallCorona:
            return;
        }
    }
}

void BigCorona::Hit()
{
    lives_--;
    effect_->setColor(kColors[lives_]);
    animation_frame_ = 1;
    if (lives_ <= 0) {
        Die();
        return;
    }
}

void BigCorona::Die()
{
    emit Scored(kBigCoronaScore);
    is_alive_ = false;
    timeline_ = new QTimeLine(400);
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
