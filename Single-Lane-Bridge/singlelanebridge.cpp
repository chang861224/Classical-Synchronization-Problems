#include "singlelanebridge.h"
#include "car.h"
#include <QSemaphore>

SingleLaneBridge::SingleLaneBridge()
{
    bridgeLen = 100;
    bridgeEntryPos[0] = 25;
    bridgeEntryPos[1] = 75;
}

void
SingleLaneBridge::run()
{
    Car *tmp[100];
    for(int iter(0); iter<100; ++iter){
        tmp[iter] = new Car();
    }

    for(int iter(0); iter<100; ++iter){
//        Car *a = new Car();
//        a->start();
//        connect(a, SIGNAL(posChanged(int, int)), this, SLOT(updatePos(int, int)));
        tmp[iter] -> start();
        connect(tmp[iter], SIGNAL(posChanged(int,int)), this, SLOT(updatePos(int,int)));
        connect(tmp[iter], SIGNAL(finished()), tmp[iter], SLOT(deleteLater()));
    }
//    a.wait();
}

void
SingleLaneBridge::updatePos(int carID, int pos)
{
    qDebug() << "Car:" << carID << ", Pos:" << pos;
}
