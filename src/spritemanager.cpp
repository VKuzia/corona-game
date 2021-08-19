#include "spritemanager.h"

QHash<int, QImage*> SpriteManager::images_ = QHash<int, QImage*>();
void SpriteManager::Init()
{
    images_[kSmallVirus] = new QImage(":/smallvirus.png");
    images_[kBigVirus] = new QImage(":/bigvirus.png");
    images_[kBlueBullet] = new QImage(":/bluebullet.png");
    images_[kRedBullet] = new QImage(":/redbullet.png");
    images_[kBsu] = new QImage(":/bsuverysmall.png");
    images_[kPin] = new QImage(":/pin.png");
    images_[kPin2] = new QImage(":/pin2.png");
    images_[kBoom] = new QImage(":/boom.png");
}

const QImage *SpriteManager::GetImage(int num)
{
    return images_[num];
}

QGraphicsColorizeEffect *SpriteManager::GetRed()
{
    QGraphicsColorizeEffect* color = new QGraphicsColorizeEffect();
    color->setColor(QColor(250,20,20));
    color->setStrength(0.5);
    return color;
}
