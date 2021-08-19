#include "graphicsunit.h"

GraphicsUnit::GraphicsUnit() : type_(-1), x_(0),
    y_(0), width_(0), height_(0), rect_(0,0,0,0), is_active_(true)
{}

GraphicsUnit::~GraphicsUnit()
{}

GraphicsUnit::GraphicsUnit(QGraphicsView* graphics_area, int type, int x, int y, int width, int height) :
    graphics_area_(graphics_area),
   type_(type),
   x_(x),
   y_(y),
   width_(width),
   height_(height),
   rect_(-width_ / 2, -height_ / 2, width_, height_),
   is_active_(true),
   paused_(false)
{
    this->setX(x_);
    this->setY(y_);
}

void GraphicsUnit::SetPaused(bool paused)
{
    paused_ = paused;
}

int GraphicsUnit::GetType() const
{
    return type_;
}

qreal GraphicsUnit::y() const
{
    return y_;
}

int GraphicsUnit::GetWidth() const
{
    return this->width_;
}

int GraphicsUnit::GetHeight() const
{
    return height_;
}


qreal GraphicsUnit::x() const
{
    return x_;
}

bool GraphicsUnit::IsActive() const
{
    return is_active_;
}

void GraphicsUnit::SetActive(bool is_active)
{
    is_active_ = is_active;
}

