#include "boom.h"

const int kBoomRadius = 500;
const int kBasicTime = 1700;
const int kBoomZValue = 10;
const int kBlurRadius = 6;
const qreal kBoomOpacity = 0.65;
const QColor kBoomColor = QColor::fromRgb(10,250,10);

Boom::Boom(QGraphicsView *graphics_area, int type, int x, int y, qreal size, qreal time) :
    GraphicsUnit (graphics_area, type, x, y, size * kBoomRadius, size * kBoomRadius),
    animation_(new QGraphicsItemAnimation(this)), timeline_(new QTimeLine(kBasicTime * time)),
    opacity_animation_(new QPropertyAnimation(this)), first_draw_(false), time_(time)
{
    this->setZValue(kBoomZValue);
    this->setVisible(false);
    timeline_->setEasingCurve(QEasingCurve::Linear);
    animation_->setItem(this);
    animation_->setTimeLine(timeline_);
    animation_->setScaleAt(0,0.1,0.1);
    animation_->setScaleAt(0.1,0.85,0.85);
    animation_->setScaleAt(1,1,1);

    QGraphicsBlurEffect* effect = new QGraphicsBlurEffect();
    effect->setBlurRadius(kBlurRadius);
    this->setGraphicsEffect(effect);

    opacity_animation_->setTargetObject(this);
    opacity_animation_->setPropertyName("opacity_");
    opacity_animation_->setStartValue(kBoomOpacity);
    opacity_animation_->setEndValue(0);
    opacity_animation_->setDuration(kBasicTime * time_);

    opacity_animation_->start();
    timeline_->start();
    connect(timeline_, &QTimeLine::finished, this, [=] {
        delete this;
    });
    graphics_area_->scene()->addItem(this);
}

Boom::~Boom()
{
    graphics_area_->scene()->removeItem(this);
    opacity_animation_->stop();
    timeline_->stop();
    delete opacity_animation_;
    delete animation_;
    delete timeline_;
}

QRectF Boom::boundingRect() const
{
    return rect_;
}

void Boom::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    if (!first_draw_) {
        first_draw_ = true;
        return;
    }
    painter->setPen(Qt::NoPen);
    painter->setBrush(kBoomColor);
    painter->drawEllipse(rect_);
}

void Boom::SetPaused(bool paused)
{
    paused_ = paused;
    if (paused) {
        timeline_->setPaused(true);
        opacity_animation_->pause();
     } else {
        timeline_->resume();
        opacity_animation_->resume();
     }
}

qreal Boom::opacity_() const
{
    return this->opacity();
}

void Boom::setOpacity_(const qreal &opacity)
{
    if (opacity < kBoomOpacity - 0.02 && !this->isVisible()) {
        setVisible(true);
    }
    this->setOpacity(opacity);
}
