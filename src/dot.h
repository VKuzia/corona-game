#ifndef DOTSPRITE_H
#define DOTSPRITE_H
#include "graphicsunit.h"

class Dot : public GraphicsUnit
{
    Q_OBJECT
public:
    Dot(QGraphicsView* graphics_area, int x, int y, QColor color, qreal size);
    ~Dot() override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void Appear();
    void Die();

signals:
    void Deleted();

private:
    QColor color_;
    QGraphicsItemAnimation* animation_;
    QTimeLine* timeline_;
    int painted_;
};

#endif // DOTSPRITE_H
