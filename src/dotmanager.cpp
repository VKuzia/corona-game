#include "dotmanager.h"
#include "utility.h"

const int kDotInterval = 2000;
const int kMaxDotCount = 29;
const int kDotScore = 1;

DotManager::DotManager(QGraphicsView *graphics_area, qreal size) :
    graphics_area_(graphics_area),
    timer_(new QTimer(graphics_area)),
    size_(size),
    dot_count_(0),
    paused_(false),
    remaining_(0)
{
    connect(timer_, &QTimer::timeout, this, [=]{
        this->AddDot();
        this->timer_->setInterval(kDotInterval);
    });
    timer_->start(kDotInterval);
}

DotManager::~DotManager()
{
    timer_->stop();
    delete timer_;
}

void DotManager::SetPaused(bool paused)
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

void DotManager::AddDot() {
    if (dot_count_ >= kMaxDotCount) {
        return;
    }
    QColor random_color = QColor(120 + Utility::generator.bounded(135),
                                 200 + Utility::generator.bounded(55),
                                 150 + Utility::generator.bounded(105));
    Dot* dot =
            new Dot(graphics_area_,
                    Utility::generator.bounded(graphics_area_->width() * 2.0 / 3.0)
                         - graphics_area_->width() / 3,
                    Utility::generator.bounded(graphics_area_->height() * 2.0 / 3.0)
                        - graphics_area_->height() / 3,
                    random_color,
                    size_);
    dot_count_++;
    connect(dot, &Dot::Deleted, this, [=] {
        dot_count_--;
        emit Scored(kDotScore);
    });
    dot->Appear();
}
