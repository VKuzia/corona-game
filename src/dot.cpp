#include "dot.h"

const int kDotRadius = 14;
const int kAppearTime = 1000;
const int kDieTime = 500;
const int kDieHeight = 100;

Dot::Dot(QGraphicsView* graphics_area, int x, int y, QColor color, qreal size) :
    GraphicsUnit(graphics_area, GraphicsUnit::kDot,x, y, size * kDotRadius, size * kDotRadius),
    color_(color),
    animation_(new QGraphicsItemAnimation()),
    timeline_(new QTimeLine()),
    painted_(0)
{
    this->setOpacity(0.001);
}

Dot::~Dot()
{
    graphics_area_->scene()->removeItem(this);
    timeline_->stop();
    delete timeline_;
    delete animation_;
}

QRectF Dot::boundingRect() const
{
    return rect_;
}

void Dot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (painted_ > 1 && painted_ < 3) {
        this->setOpacity(1);
    }
    painted_ = qMin(3, painted_ + 1);
    painter->setBrush(color_);
    painter->setPen(color_);
    painter->drawEllipse(rect_);
}

void Dot::Appear()
{
    timeline_ = new QTimeLine(kAppearTime);
    animation_ = new QGraphicsItemAnimation();
    animation_->setItem(this);
    animation_->setTimeLine(timeline_);
    animation_->setScaleAt(0, 0, 0);
    animation_->setScaleAt(1, 1, 1);
    timeline_->start();
    connect(timeline_, &QTimeLine::finished, this, [=]{});

    graphics_area_->scene()->addItem(this);
}

void Dot::Die()
{
    if (!is_active_) {
        return;
    }
    timeline_->stop();
    delete timeline_;
    delete animation_;
    is_active_ = false;
    timeline_ = new QTimeLine(kDieTime);
    animation_ = new QGraphicsItemAnimation();
    animation_->setItem(this);
    animation_->setTimeLine(timeline_);
    animation_->setPosAt(0, QPointF(x_, y_));
    animation_->setPosAt(1, QPointF(x_, y_ - kDieHeight));

        animation_->setScaleAt(0, 1,1);
        animation_->setScaleAt(0.2, 2, 2);
        animation_->setScaleAt(1, 0,0);

    timeline_->setEasingCurve(QEasingCurve::Linear);
    connect(timeline_, &QTimeLine::finished, this, [=] {
        delete this;});
    timeline_->start();
    emit Deleted();
}

