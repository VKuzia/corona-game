#ifndef GRAPHICSAREA_H
#define GRAPHICSAREA_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include "drawer.h"
#include "mousepin.h"
#include "bullet.h"
#include "dotmanager.h"
#include "mobmanager.h"
#include "boom.h"
#include "coronabullet.h"

class GraphicsArea : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsArea(QWidget* parent);
    ~GraphicsArea() override;
    void Resized();

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;

    void DifficultyChanged(int difficulty);
    void SpeedChanged(int speed);

    int GetWidth() const;
    int GetHeight() const;
    int64_t GetScore() const;
    bool GetPaused() const;
    bool getIs_losable() const;
    void setIs_losable(bool value);

public slots:
    void Tick();
    void Score(int num);
    void Pause();
    void Retry();
    void Lose();

signals:
    void Scored();

private:
    int width_;
    int height_;

    QGraphicsScene* scene_;
    Drawer* drawer_;
    QGraphicsRectItem* move_rect_;
    QTimer* timer_;
    MousePin* pin_;
    DotManager* dot_manager_;
    MobManager* mob_manager_;

    int64_t score_;
    bool paused_;
    bool is_losable_;
    bool finished_;

    int difficulty_;
    int speed_;
    qreal Size() const;

    void Clear();
    void SetUp();
    bool OutOfBounds(int x, int y) const;

};

#endif // GRAPHICSAREA_H
