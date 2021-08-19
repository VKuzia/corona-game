#include "mousepinsprite.h"
#include "spritemanager.h"

const int kMousePinWidth = 29;
const int kMousePinHeight = 29;
const int kDefaultTransparency = 200;

MousePinSprite::MousePinSprite(QGraphicsView* graphics_area, int x, int y, qreal size) :
    GraphicsUnit (graphics_area, GraphicsUnit::kPin, x, y, kMousePinWidth * size, kMousePinHeight * size),
    transparency_(kDefaultTransparency)
{
    this->setZValue(1);
}

MousePinSprite::~MousePinSprite() {}

QRectF MousePinSprite::boundingRect() const
{
    return rect_;
}

void MousePinSprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setOpacity(transparency_ / 255.0);
    painter->drawImage(rect_, *SpriteManager::GetImage(SpriteManager::kPin));
}

void MousePinSprite::Update(int x, int y)
{
    moveBy(x-x_, y-y_);
    update();
    x_ = x;
    y_ = y;
}

void MousePinSprite::HandleCollisions() {
    for (auto item : this->collidingItems()) {
        GraphicsUnit* item_s = dynamic_cast<GraphicsUnit*>(item);
        if (item_s == nullptr) {
            continue;
        }
        switch(item_s->GetType()) {
            case GraphicsUnit::kCoronaBullet:
            if (item_s->isActive()) {
                item_s->setVisible(false);
                dynamic_cast<CoronaBullet*>(item_s)->Die();
           }
        }
    }
}
