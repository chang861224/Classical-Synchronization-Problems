#include "singlelanebridge.h"
#include "car.h"
#include <QSemaphore>

SingleLaneBridge::SingleLaneBridge()
{
    if(eastTrafficLight -> available() > 0) east2west = true;
    else if(westTrafficLight -> available() > 0) east2west = false;
}

void
SingleLaneBridge::run()
{
    Car *upLaneCars[50], *downLaneCars[50];
    for(int iter(0); iter < 50; ++iter){
        upLaneCars[iter] = new Car(false);
        upLaneCars[iter] -> setTrafficLight(westTrafficLight, eastTrafficLight);
        downLaneCars[iter] = new Car(true);
        downLaneCars[iter] -> setTrafficLight(westTrafficLight, eastTrafficLight);
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

        QThread::currentThread() -> msleep(1200);
    }
}

void
SingleLaneBridge::updatePos(int carID, int pos)
{
    qDebug() << "Car:" << carID << ", Pos:" << pos;
}

void
SingleLaneBridge::switchLight()
{
    if(east2west){
        for(int iter(0); iter < kMaxCars2Pass; ++iter) eastTrafficLight -> acquire(1);
        westTrafficLight -> release(kMaxCars2Pass);
    } else {
        for(int iter(0); iter < kMaxCars2Pass; ++iter) westTrafficLight -> acquire(1);
        eastTrafficLight -> release(kMaxCars2Pass);
    }
}
