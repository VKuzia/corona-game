#ifndef SMALLCORONA_H
#define SMALLCORONA_H
#include "mob.h"
#include "utility.h"

class SmallCorona : public Mob
{
    Q_OBJECT
public:
    SmallCorona(QGraphicsView* graphics_view, int x, int y, qreal size, qreal speed);
    ~SmallCorona() override;
    QRectF boundingRect() const override;
    void SetPaused(bool paused) override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void Update(int drawer_x, int drawer_y);
    void SetItems();
    void SetSpeed(int speed);
signals:
    void Scored(int);

private:
    qreal speed_;
    QGraphicsItemAnimation* animation_;
    QTimeLine* timeline_;
    qreal current_x_;
    qreal current_y_;
    int frame_counter_;
    void HandleCollisions();
    void Die();
};

#endif // SMALLCORONA_H
