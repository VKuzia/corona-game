#ifndef BOOM_H
#define BOOM_H
#include "graphicsunit.h"

class Boom : public GraphicsUnit
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity_ READ opacity_ WRITE setOpacity_)

public:
    Boom(QGraphicsView* graphics_area, int type, int x, int y, qreal size, qreal time);
    ~Boom() override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void SetPaused(bool paused) override;
private:
    QGraphicsItemAnimation* animation_;
    QTimeLine* timeline_;
    QPropertyAnimation* opacity_animation_;
    bool first_draw_;
    qreal time_;
    int remaining_;

    qreal opacity_() const;
    void setOpacity_(const qreal &opacity);
};

#endif // BOOM_H
