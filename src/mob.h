#ifndef MOB_H
#define MOB_H
#include "graphicsunit.h"

class Mob : public GraphicsUnit
{
    Q_OBJECT
public:
    Mob(QGraphicsView* graphics_area, int type, int x, int y, int width, int height);
    virtual ~Mob() override;

    virtual void SetPaused(bool paused) override;
    int x() const;
    int y() const;
    bool is_alive() const;

protected:
    bool is_alive_;
};

#endif // MOB_H
