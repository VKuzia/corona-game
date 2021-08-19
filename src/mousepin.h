#ifndef MOUSEPIN_H
#define MOUSEPIN_H
#include <QGraphicsView>
#include "mousepinsprite.h"
#include "utility.h"

class MousePin : public QObject
{
    Q_OBJECT
public:
    MousePin(QGraphicsView* graphics_area, qreal size);
    ~MousePin() override;

    void SetItems(qreal size);
    void Update(int x, int y, bool set_items);
    void SetPaused(bool paused);
    QGraphicsItem* GetSprite();

private:
    QGraphicsView* graphics_area_;
    QVector<MousePinSprite*> sprites_;
    int x_;
    int y_;
    qreal radius_;
    int sprite_num_;
    bool first_update_;
    bool paused_;
    qreal size_;
};

#endif // MOUSEPIN_H
