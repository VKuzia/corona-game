#include "graphicsarea.h"

const int kDrawerReloadFrames = 500;
const int kDefaultDifficulty = 50;
const int kDefaultSpeed = 50;
const int kFps = 50;
const QColor kBackground = QColor::fromRgb(80,80,80);
const int kOutOfBounds = 100;

GraphicsArea::GraphicsArea(QWidget* parent) : QGraphicsView(parent),
    width_(this->width()),
    height_(this->height()),
    scene_(new QGraphicsScene()),
    is_losable_(false),
    difficulty_(kDefaultDifficulty),
    speed_(kDefaultSpeed)
{
    this->setScene(scene_);
    this->setSceneRect(-width_ / 2, -height_ / 2, width_ , height_);
    this->setBackgroundBrush(QBrush(kBackground));
    this->setRenderHints(QPainter::Antialiasing);

    SetUp();
    timer_->start(1000 / kFps);
}

GraphicsArea::~GraphicsArea()
{
    Clear();
}

void GraphicsArea::Resized()
{
    pin_->SetItems(Size());
    height_ = this->height();
    width_ = this->width();
}

void GraphicsArea::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
     case Qt::Key_Space:
        Pause();
        break;
     case Qt::Key_W:
         drawer_->setUp(true);
     break;
     case Qt::Key_S:
            drawer_->setDown(true);
     break;
     case Qt::Key_A:
         drawer_->setLeft(true);
      break;
     case Qt::Key_D:
         drawer_->setRight(true);
     break;
    }
}

void GraphicsArea::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()) {
     case Qt::Key_Escape:
        Retry();
        break;
     case Qt::Key_W:
         drawer_->setUp(false);
     break;
     case Qt::Key_S:
            drawer_->setDown(false);
     break;
     case Qt::Key_A:
         drawer_->setLeft(false);
      break;
     case Qt::Key_D:
         drawer_->setRight(false);
     break;
    }
}

void GraphicsArea::mousePressEvent(QMouseEvent* event)
{
    if (paused_) {
        return;
    }
    if (event->button() == Qt::RightButton) {
        if (drawer_->reload() < kDrawerReloadFrames) {
            return;
        }
        drawer_->setReload(0);
        new Boom(this, GraphicsUnit::kBigBoom, drawer_->x(), drawer_->y(), Size(), 1);
    } else {
        new Bullet(this, drawer_->x(), drawer_->y(),Size(), Size());
    }
}

void GraphicsArea::DifficultyChanged(int difficulty)
{
    difficulty_ = difficulty;
    mob_manager_->setDifficulty(difficulty);
}

void GraphicsArea::SpeedChanged(int speed)
{
    speed_ = speed;
    mob_manager_->setSpeed(speed);
}

void GraphicsArea::Tick()
{
    if (paused_) {
        return;
    }
    drawer_->Update();
    pin_->Update(drawer_->x(), drawer_->y(), false);
    mob_manager_->Update(drawer_->x(), drawer_->y());
}

int64_t GraphicsArea::GetScore() const
{
    return score_;
}

void GraphicsArea::Score(int num)
{
    score_ += num;
    emit Scored();
}

void GraphicsArea::Pause()
{
    if (finished_) {
        return;
    }
    paused_ = !paused_;
    if (paused_) {
        timer_->stop();
    } else {
        timer_->start();
    }
    drawer_->SetPaused(paused_);
    pin_->SetPaused(paused_);
    mob_manager_->SetPaused(paused_);
    dot_manager_->SetPaused(paused_);
    GraphicsUnit* current_unit;
    for (auto unit : scene()->items()) {
        current_unit = dynamic_cast<GraphicsUnit*>(unit);
        if (current_unit != nullptr) {
            current_unit->SetPaused(paused_);
        }
    }
}

void GraphicsArea::Retry()
{
    if (!paused_) {
        Pause();
    }
    Clear();
    SetUp();
    timer_->start(1000 / kFps);
}

void GraphicsArea::Lose()
{
    Pause();
    finished_ = true;
}

bool GraphicsArea::getIs_losable() const
{
    return is_losable_;
}

void GraphicsArea::setIs_losable(bool value)
{
    drawer_->setIs_losable(value);
    is_losable_ = value;
}

bool GraphicsArea::GetPaused() const
{
    return paused_;
}

int GraphicsArea::GetHeight() const
{
    return height_;
}

int GraphicsArea::GetWidth() const
{
    return width_;
}

qreal GraphicsArea::Size() const
{
    return 1;
}

void GraphicsArea::Clear()
{
    if (!paused_) {
        Pause();
    }
    delete timer_;
    delete pin_;
    delete dot_manager_;
    delete mob_manager_;
//    this->scene()->clear();
    GraphicsUnit* unit;
    for (auto item: this->scene()->items()) {
        unit = dynamic_cast<GraphicsUnit*>(item);
        if (unit == nullptr) {
            continue;
        }
        switch (unit->GetType()) {
        case GraphicsUnit::kDot:
            delete dynamic_cast<Dot*>(unit);
            break;
        case GraphicsUnit::kPin:
            delete dynamic_cast<MousePinSprite*>(unit);
            break;
        case GraphicsUnit::kDrawer:
            delete dynamic_cast<Drawer*>(unit);
            break;
        case GraphicsUnit::kSmallCorona:
            delete dynamic_cast<SmallCorona*>(unit);
            break;
        case GraphicsUnit::kBigCorona:
            delete dynamic_cast<BigCorona*>(unit);
            break;
        case GraphicsUnit::kBullet:
            delete dynamic_cast<Bullet*>(unit);
            break;
        case GraphicsUnit::kCoronaBullet:
            delete dynamic_cast<CoronaBullet*>(unit);
            break;
        case GraphicsUnit::kBoom:
            delete dynamic_cast<Boom*>(unit);
            break;
        case GraphicsUnit::kBigBoom:
            delete dynamic_cast<Boom*>(unit);
            break;
        }
    }
}

void GraphicsArea::SetUp()
{
    score_ = 0;
    paused_ = false;
    finished_ = false;
    drawer_ = new Drawer(this, Size(), is_losable_);
    timer_ = new QTimer(this);
    pin_ = new MousePin(this, Size());
    dot_manager_ = new DotManager(this, Size());
    mob_manager_ = new MobManager(this, kDefaultDifficulty, kDefaultSpeed, Size());

    DifficultyChanged(difficulty_);
    SpeedChanged(speed_);

    pin_->SetItems(Size());
    drawer_->SetItems(Size());

    connect(drawer_, SIGNAL(Lost()), this, SLOT(Lose()));
    connect(timer_, SIGNAL(timeout()), this, SLOT(Tick()));
    connect(dot_manager_, SIGNAL(Scored(int)), this, SLOT(Score(int)));
    connect(mob_manager_, SIGNAL(Scored(int)), this, SLOT(Score(int)));
}

bool GraphicsArea::OutOfBounds(int x, int y) const
{
    return !((x > -kOutOfBounds - width() / 2) &&
             (x < this->width() / 2 + kOutOfBounds) &&
             (y > -kOutOfBounds - height() / 2) &&
             (y < this->height() / 2 + kOutOfBounds));
}
