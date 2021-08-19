#include <QApplication>
#include "mainwindow.h"
#include "spritemanager.h"

int main(int argc, char *argv[])
{
    SpriteManager::Init();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.SetStarted(true);

    return a.exec();
}
