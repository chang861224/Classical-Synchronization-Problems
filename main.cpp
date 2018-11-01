#include "mainwindow.h"
#include <QApplication>
#include <QSemaphore>
#include "Single-Lane-Bridge/singlelanebridge.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    SingleLaneBridge b;
    b.start();
//    b.run();

    return a.exec();
}
