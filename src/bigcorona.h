#ifndef BIGCORONA_H
#define BIGCORONA_H
#include <QGraphicsColorizeEffect>
#include <QTimer>
#include "mob.h"
#include "utility.h"

class BigCorona : public Mob
{
    Q_OBJECT
public:
    BigCorona(QGraphicsView* graphics_view, int x, int y, qreal size, qreal speed);
    ~BigCorona() override;
    QRectF boundingRect() const override;
    void SetPaused(bool paused) override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void Shoot(int drawer_x, int drawer_y) const;
    void Update(int drawer_x, int drawer_y);
    void SetItems();
    void SetSpeed(int speed);
signals:
    void Scored(int);

private:
    qreal speed_;
    QGraphicsItemAnimation* animation_;
    QTimeLine* timeline_;
    QTimer* timer_;
    int frame_counter_;
    int lives_;
    GraphicsUnit* last_pin_;
    QGraphicsColorizeEffect* effect_;
    int animation_frame_;
    int remaining_;
    bool time_to_shoot_;

    void HandleCollisions();
    void Hit();
    void Die();
};

#endif // BIGCORONA_H
