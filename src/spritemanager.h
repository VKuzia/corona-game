#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H
#include <QImage>
#include <QHash>
#include <QGraphicsColorizeEffect>

class SpriteManager
{
public:
    enum Images{
        kSmallVirus,
        kBigVirus,
        kBlueBullet,
        kRedBullet,
        kBsu,
        kPin,
        kPin2,
        kBoom
    };
    static void Init();
    static const QImage* GetImage(int num);
    static QGraphicsColorizeEffect* GetRed();
private:
    static QHash<int, QImage*> images_;
};

#endif // SPRITEMANAGER_H
