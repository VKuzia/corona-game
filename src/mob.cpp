#include "mob.h"

Mob::Mob(QGraphicsView *graphics_area, int type, int x, int y, int width, int height) :
    GraphicsUnit(graphics_area, type, x, y, width, height),
    is_alive_(true) {}

Mob::~Mob() {}

void Mob::SetPaused(bool paused)
{
    paused_ = paused;
}

int Mob::x() const
{
    return x_;
}

int Mob::y() const
{
    return y_;
}

bool Mob::is_alive() const
{
    return is_alive_;
}
