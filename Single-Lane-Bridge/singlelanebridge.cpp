#include "singlelanebridge.h"
#include "car.h"
#include <QSemaphore>

SingleLaneBridge::SingleLaneBridge()
{
}

void
SingleLaneBridge::run()
{
    Car *upLaneCars[50], *downLaneCars[50];
    for(int iter(0); iter < 50; ++iter){
        upLaneCars[iter] = new Car();
        downLaneCars[iter] = new Car(1);
    }

    for(int iter(0); iter < 10; ++iter){
        upLaneCars[iter] -> start();
        connect(upLaneCars[iter], SIGNAL(posChanged(int,int)), this, SIGNAL(carChanged(int,int)));
        connect(upLaneCars[iter], SIGNAL(finished()), upLaneCars[iter], SLOT(deleteLater()));
        connect(upLaneCars[iter], SIGNAL(finished(int)), this, SIGNAL(deleteCar(int)));

        downLaneCars[iter] -> start();
        connect(downLaneCars[iter], SIGNAL(posChanged(int,int)), this, SIGNAL(carChanged(int,int)));
        connect(downLaneCars[iter], SIGNAL(finished()), downLaneCars[iter], SLOT(deleteLater()));
        connect(downLaneCars[iter], SIGNAL(finished(int)), this, SIGNAL(deleteCar(int)));

        QThread::currentThread() -> msleep(1000);
    }
//    a.wait();
}

void
SingleLaneBridge::updatePos(int carID, int pos)
{
    qDebug() << "Car:" << carID << ", Pos:" << pos;
}
