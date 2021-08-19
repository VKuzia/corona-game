#ifndef MOBMANAGER_H
#define MOBMANAGER_H

#include <QObject>
#include <QTimer>
#include <QGraphicsView>
#include <QSet>
#include "utility.h"
#include "smallcorona.h"
#include "bigcorona.h"

class MobManager : public QObject
{
    Q_OBJECT
public:
    MobManager(QGraphicsView* graphics_area_, int difficulty, int speed, qreal size);
    ~MobManager() override;
    void Update(int drawer_x, int drawer_y);

    void SetPaused(bool);
    void setDifficulty(int difficulty);
    void setSpeed(int speed);

signals:
    void Scored(int num);

public slots:
    void LaunchSmallCorona();
    void LaunchBigCorona();
    void Score(int num);

private:
    QGraphicsView* graphics_area_;
    QTimer* small_corona_timer_;
    QTimer* big_corona_timer_;
    QSet<SmallCorona*> small_coronas_;
    QSet<BigCorona*> big_coronas_;
    bool paused_;
    int remaining_;
    int remaining_big_;
    int difficulty_;
    int small_corona_speed_; 
    qreal size_;

    QPoint GetRandomStart();
};

#endif // MOBMANAGER_H
