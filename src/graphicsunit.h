#ifndef GRAPHICSELEMENT_H
#define GRAPHICSELEMENT_H
#include <QGraphicsView>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QGraphicsItem>
#include <QPropertyAnimation>
#include <QPainter>
#include "spritemanager.h"

class GraphicsUnit : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum type {
       kDrawer,
       kPin,
       kBullet,
       kDot,
       kSmallCorona,
       kBigCorona,
       kBot,
       kBoom,
       kBigBoom,
       kCoronaBullet
    };
    GraphicsUnit();
    virtual ~GraphicsUnit() override;
    GraphicsUnit(QGraphicsView* graphics_area, int type, int x, int y, int width, int height);
    QRectF boundingRect() const override = 0;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override = 0;

    virtual void SetPaused(bool paused_);

    int GetType() const;
    qreal x() const;
    qreal y() const;
    int GetWidth() const;
    int GetHeight() const;
    bool IsActive() const;

    void SetActive(bool is_active);

protected:
    QGraphicsView* graphics_area_;
    int type_;
    qreal x_;
    qreal y_;
    int width_;
    int height_;
    QRectF rect_;
    bool is_active_;
    bool paused_;
};

#endif // GRAPHICSELEMENT_H
