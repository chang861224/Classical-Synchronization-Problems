#include "singlelanebridge.h"
#include "car.h"
#include <QSemaphore>

SingleLaneBridge::SingleLaneBridge()
{
}

void
SingleLaneBridge::run()
{
    Car *tmp[100];
    for(int iter(0); iter<100; ++iter){
        tmp[iter] = new Car();
    }

    for(int iter(0); iter<1; ++iter){
        tmp[iter] -> start();
        connect(tmp[iter], SIGNAL(posChanged(int,int)), this, SIGNAL(carChanged(int,int)));
        connect(tmp[iter], SIGNAL(finished()), tmp[iter], SLOT(deleteLater()));
    }
//    a.wait();
}

void
SingleLaneBridge::updatePos(int carID, int pos)
{
    qDebug() << "Car:" << carID << ", Pos:" << pos;
}
