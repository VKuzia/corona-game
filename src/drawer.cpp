#include "drawer.h"
#include "graphicsunit.h"
#include "spritemanager.h"
#include "utility.h"

const int kDrawerWidth = 52;
const int kDrawerHeight = 52;
const int kDrawerSpeed = 7;
const int kDrawerOffset = 6;
const qreal kDrawerZValue = -100;
const int kDrawerReloadFrames = 500;
const QColor kDrawerReloading = QColor::fromRgb(235, 195, 52, 100);
const QColor kDrawerReloaded =  QColor::fromRgb(0, 255, 0, 100);

Drawer::Drawer(QGraphicsView* graphics_area, qreal size, bool is_losable) :
    GraphicsUnit(graphics_area, GraphicsUnit::kDrawer, 0, 0, size * kDrawerWidth, size * kDrawerHeight),
    up_(false),
    down_(false),
    left_(false),
    right_(false),
    speed(kDrawerSpeed),
    size_(size),
    offset_(kDrawerOffset),
    is_losable_(is_losable),
    reload_(0)
{
    this->setOpacity(0.8);
    setZValue(kDrawerZValue);
    paused_ = false;
    rect_ = QRectF(-offset_ - width_ / 2, -offset_ - height_ / 2,
                   width_ + offset_ * 2, height_ + offset_ * 2);
}

Drawer::~Drawer() {
    graphics_area_->scene()->removeItem(this);
}

QRectF Drawer::boundingRect() const
{
    return rect_;
}

void Drawer::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setOpacity(0.25);
    painter->drawImage(QRectF(rect_.x() + offset_ + shadow_offset_x_,
                       rect_.y() + offset_ + shadow_offset_y_,
                       rect_.width() - offset_ * 2,
                       rect_.height() - offset_ * 2),
                       *SpriteManager::GetImage(SpriteManager::kBsu));
    painter->setOpacity(0.5);
    painter->drawImage(QRectF(rect_.x() + offset_ + shadow_offset_x_ / 2,
                              rect_.y() + offset_ + shadow_offset_y_ / 2,
                              rect_.width() - offset_ * 2,
                              rect_.height() - offset_ * 2),
                       *SpriteManager::GetImage(SpriteManager::kBsu));
    painter->setOpacity(1);
    painter->drawImage(QRectF(rect_.x() + offset_,
                              rect_.y() + offset_,
                              rect_.width() - offset_ * 2,
                              rect_.height() - offset_ * 2),
                       *SpriteManager::GetImage(SpriteManager::kBsu));
    reload_ = qMin(kDrawerReloadFrames, reload_ + 1);
    painter->setBrush((reload_ < kDrawerReloadFrames ?
                       kDrawerReloading:
                       kDrawerReloaded));
    painter->drawRect(QRectF(rect_.x() + offset_,
                                    rect_.y() + offset_ + shadow_offset_y_,
                                    (rect_.width() - offset_ * 2) * 1.0 * reload_ / kDrawerReloadFrames,
                                    (rect_.height() - offset_ * 2) / 7));
}

void Drawer::Update()
{
    if (paused_) {
        return;
    }
    int last_x = x_;
    int last_y = y_;
    shadow_offset_x_ = 0;
    shadow_offset_y_ = 0;
    if (up_) {
       y_ -= speed;
       shadow_offset_y_ = offset_;
    }
    if (down_) {
       y_ += speed;
       shadow_offset_y_ = -offset_;
    }
    if (left_) {
       x_ -= speed;
       shadow_offset_x_ = offset_;
    }
    if (right_) {
       x_ += speed;
       shadow_offset_x_ = -offset_;
    }
    if (x_ > graphics_area_->width() / 2 || x_ < - graphics_area_->width()/2){
        x_ = last_x;
    }
    if (y_ > graphics_area_->height() / 2 || y_ < - graphics_area_->height()/2){
        y_ = last_y;
    }
    setX(x_);
    setY(y_);
    this->update();
    HandleCollisions();
}

void Drawer::SetItems(qreal size)
{
    size_ = size;
    graphics_area_->scene()->addItem(this);
    reload_ = 0;
    this->setZValue(kDrawerZValue);
    Update();
}

void Drawer::SetPaused(bool paused)
{
    paused_ = paused;
}

void Drawer::setUp(bool up)
{
    up_ = up;
}

void Drawer::setDown(bool down)
{
    down_ = down;
}

void Drawer::setLeft(bool left)
{
    left_ = left;
}

void Drawer::setRight(bool right)
{
    right_ = right;
}

void Drawer::EatDot(Dot *dot)
{
    dot->Die();
    emit Scored();
}

void Drawer::Lose()
{
    this->setGraphicsEffect(SpriteManager::GetRed());
    emit Lost();
}

void Drawer::setIs_losable(bool is_losable)
{
    is_losable_ = is_losable;
}

int Drawer::reload() const
{
    return reload_;
}

void Drawer::setReload(int reload)
{
    reload_ = reload;
}

void Drawer::HandleCollisions() {
    for (auto item : this->collidingItems()) {
        GraphicsUnit* item_s = dynamic_cast<GraphicsUnit*>(item);
        if (item_s == nullptr) {
            continue;
        }
        switch(item_s->GetType()) {
            case GraphicsUnit::kDot :
                EatDot(dynamic_cast<Dot*>(item_s));
                break;
            case GraphicsUnit::kBigCorona:
            case GraphicsUnit::kSmallCorona :
               if (is_losable_) {
                   if (Utility::Distance(item_s->x(), item_s->y(), this->x(), this->y()) <
                           this->GetWidth() / 2 + item_s->GetWidth() / 2) {
                       Lose();
                       item_s->setZValue(1000);
                   }
               }
               return;
            case GraphicsUnit::kCoronaBullet:
            if(is_losable_) {
                Lose();
                return;
            }
        }
    }
}
