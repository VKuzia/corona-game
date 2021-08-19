#ifndef DOTMANAGER_H
#define DOTMANAGER_H
#include <QTimer>
#include "dot.h"

class DotManager : public QObject
{
    Q_OBJECT
public:
    DotManager(QGraphicsView* graphics_area , qreal size);
    ~DotManager() override;
    void SetPaused(bool);

public slots:
    void AddDot();

signals:
    void Scored(int);

private:
    QGraphicsView* graphics_area_;
    QTimer* timer_;
    qreal size_;
    int dot_count_;
    bool paused_;
    int remaining_;

};

#endif // DOTMANAGER_H
