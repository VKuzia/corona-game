#ifndef DRAWER_H
#define DRAWER_H
#include "graphicsunit.h"
#include "dot.h"

class Drawer : public GraphicsUnit
{
    Q_OBJECT
public:
    Drawer(QGraphicsView* graphics_area, qreal size, bool is_losable);
    ~Drawer() override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void Update();
    void SetItems(qreal size);
    void EatDot(Dot* dot);
    void Lose();
    void SetPaused(bool) override;

    void setUp(bool up);
    void setDown(bool down);
    void setLeft(bool left);
    void setRight(bool right);
    int reload() const;
    void setReload(int reload);
    void setIs_losable(bool is_losable);

signals:
    void Scored();
    void Lost();

private:
    bool up_;
    bool down_;
    bool left_;
    bool right_;
    int speed;
    qreal size_;
    int shadow_offset_x_;
    int shadow_offset_y_;
    int offset_;
    bool is_losable_;
    int reload_;

    void HandleCollisions();
};

#endif // DRAWER_H
