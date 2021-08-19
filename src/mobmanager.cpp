#include "mobmanager.h"

const int kMobSpawnOffset = 70;
const int kMaxCoronaCount = 51;
const int kMaxBigCoronaCount = 7;
const int kBasicSmallInterval = 30;
const int kBasicBigInterval = 90;

MobManager::MobManager(QGraphicsView *graphics_area, int difficulty, int speed, qreal size) : graphics_area_(graphics_area),
    small_corona_timer_(new QTimer(graphics_area_)),
    big_corona_timer_(new QTimer(graphics_area_)),
    small_coronas_(), big_coronas_(), paused_(false),
    remaining_(0),
    remaining_big_(0),
    difficulty_(difficulty),
    small_corona_speed_(speed),
    size_(size)
{
    setDifficulty(difficulty_);
}

MobManager::~MobManager()
{
    small_corona_timer_->stop();
    delete small_corona_timer_;
    small_coronas_.clear();

    big_corona_timer_->stop();
    delete big_corona_timer_;
    big_coronas_.clear();
}

void MobManager::Update(int drawer_x, int drawer_y)
{
    for (auto item : small_coronas_) {
        if (!item->is_alive()) {
            small_coronas_.remove(item);
        }
        item->Update(drawer_x, drawer_y);
    }
    for (auto item : big_coronas_) {
        if (!item->is_alive()) {
            big_coronas_.remove(item);
        }
        item->Update(drawer_x, drawer_y);
    }
}

void MobManager::SetPaused(bool paused)
{
    paused_ = paused;
    if (paused) {
       remaining_ = small_corona_timer_->remainingTime();
       small_corona_timer_->stop();
       small_corona_timer_->setInterval(remaining_);

       remaining_big_ =big_corona_timer_->remainingTime();
       big_corona_timer_->stop();
       big_corona_timer_->setInterval(remaining_big_);
    } else {
        small_corona_timer_->start();
        big_corona_timer_->start();
    }
}
QPoint MobManager::GetRandomStart()
{
    if ( Utility::generator.generate() % 2) {
        return QPoint(Utility::generator.bounded(graphics_area_->width())
                      - graphics_area_->width() / 2,
                      (Utility::generator.generate() % 2 ?
                           -kMobSpawnOffset -  graphics_area_->height() / 2 :
                           graphics_area_->height() / 2 + kMobSpawnOffset));
    }
    return QPoint((Utility::generator.generate() % 2 ?
                       -kMobSpawnOffset - graphics_area_->width() / 2 :
                       graphics_area_->width() / 2 + kMobSpawnOffset),
                   Utility::generator.bounded(graphics_area_->height())
                        - graphics_area_->height() / 2);
}

void MobManager::LaunchSmallCorona()
{
    if (small_coronas_.size() > kMaxCoronaCount) {
        return;
    }
    QPoint coord = GetRandomStart();
    SmallCorona* small_corona_ = new SmallCorona(graphics_area_, coord.x(), coord.y(), size_, size_);
    small_corona_->SetSpeed(small_corona_speed_);
    connect(small_corona_, SIGNAL(Scored(int)), this, SLOT(Score(int)));
    small_corona_->SetItems();
    small_coronas_.insert(small_corona_);
}

void MobManager::LaunchBigCorona()
{
    if (big_coronas_.size() > kMaxBigCoronaCount) {
        return;
    }
    QPoint coord = GetRandomStart();
    BigCorona* big_corona_ = new BigCorona(graphics_area_, coord.x(), coord.y(), size_, size_);
    big_corona_->SetSpeed(small_corona_speed_);
    connect(big_corona_, SIGNAL(Scored(int)), this, SLOT(Score(int)));
    big_corona_->SetItems();
    big_coronas_.insert(big_corona_);
}

void MobManager::Score(int num)
{
    emit Scored(num);
}

void MobManager::setDifficulty(int difficulty)
{
    difficulty_ = difficulty;
    small_corona_timer_->stop();
    big_corona_timer_->stop();
    delete small_corona_timer_;
    delete big_corona_timer_;
    small_corona_timer_ = new QTimer(graphics_area_);
    big_corona_timer_ = new QTimer(graphics_area_);
    connect(small_corona_timer_, &QTimer::timeout, this, [this] {
        this->LaunchSmallCorona();
        this->small_corona_timer_->setInterval(kBasicSmallInterval * (100 - difficulty_));
    });
    connect(big_corona_timer_, &QTimer::timeout, this, [this] {
        this->LaunchBigCorona();
        this->big_corona_timer_->setInterval(kBasicBigInterval * (100 - difficulty_));
    });
    small_corona_timer_->start(kBasicSmallInterval * (100 - difficulty_));
    big_corona_timer_->start(kBasicBigInterval * (100 - difficulty_));
}

void MobManager::setSpeed(int speed)
{
    small_corona_speed_ = speed;
    for (auto item : small_coronas_) {
        if (!item->is_alive()) {
            small_coronas_.remove(item);
        }
        item->SetSpeed(speed);
    }
    for (auto item : big_coronas_) {
        if (!item->is_alive()) {
            big_coronas_.remove(item);
        }
        item->SetSpeed(speed);
    }
}

