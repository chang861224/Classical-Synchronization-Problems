#include "singlelanebridge.h"
#include "car.h"
#include "trafficcontrol.h"
#include <QSemaphore>
#include <QTimer>

SingleLaneBridge::SingleLaneBridge()
{
    if(eastTrafficLight -> available() > 0) east2west = true;
    else if(westTrafficLight -> available() > 0) east2west = false;

    upCarsCount = 0;
    downCarsCount = 0;
    trafficLightChange = new bool(false);
    carWidth = 60;
    createFreq = 800;
    carAmount = 0;

    QTimer *timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(checkTraffic()));
    timer -> start(1000);
}

void
SingleLaneBridge::run()
{
    trafficControler = new TrafficControl;
    trafficControler -> setCarPass(trafficLightChange);
    trafficControler -> setTrafficLight(westTrafficLight, eastTrafficLight);

    Car *lastUpCar(NULL), *lastDownCar(NULL), *currCar;
    for(int iter(0); iter < INT_MAX; ++iter) {
        while(iter >= carAmount) QThread::currentThread() -> msleep(100);

        if(iter % 2) {
            currCar = new Car(true, 7);
            ++downCarsCount;
        } else {
            currCar = new Car(false, 7);
            ++upCarsCount;
        }
        currCar -> setTrafficLight(westTrafficLight, eastTrafficLight);
        currCar -> setCarPass(trafficLightChange);

        if(currCar -> getDirection()) {
            if(lastDownCar == NULL || lastDownCar->getPos() == bridgeLen) {
                currCar -> setMaxDistance(bridgeLen);
            } else {
                lastDownCar -> setBackCar(currCar);
                currCar -> setMaxDistance(lastDownCar->getPos() - carWidth);  
            } lastDownCar = currCar;
        } else {
            if(lastUpCar == NULL || lastUpCar->getPos() == bridgeLen) {
                currCar -> setMaxDistance(bridgeLen);
            } else {
                lastUpCar -> setBackCar(currCar);
                currCar -> setMaxDistance(lastUpCar->getPos() - carWidth);
            } lastUpCar = currCar;
        }
        connect(currCar, SIGNAL(backCarMaxDistance(Car*,int)), this, SLOT(updatePos(Car*,int)));

        currCar -> start();
        connect(currCar, SIGNAL(posChanged(int,int)), this, SIGNAL(carChanged(int,int)));
        connect(currCar, SIGNAL(finished()), currCar, SLOT(deleteLater()));
        connect(currCar, SIGNAL(finished(int)), this, SIGNAL(deleteCar(int)));
        connect(currCar, SIGNAL(enterBridge(bool)), this, SLOT(setEnterCar(bool)));

        QThread::currentThread() -> msleep(unsigned(createFreq));
    }
}

void
SingleLaneBridge::updatePos(Car *car, int pos)
{
    if((car -> getBackCar()) != NULL) {
        Car *backCar = (car -> getBackCar());
        if(pos == bridgeLen) backCar -> setMaxDistance(bridgeLen);
        else backCar -> setMaxDistance(pos - carWidth);
    }
}

void
SingleLaneBridge::setEnterCar(bool direction)
{
    if(direction) --downCarsCount;
    else --upCarsCount;
}

void
SingleLaneBridge::init()
{
    this -> start();
}

void
SingleLaneBridge::setCarWidth(int width)
{
    carWidth = width;
}

void
SingleLaneBridge::setCreateFreq(int ms)
{
    createFreq = ms;
}

void
SingleLaneBridge::createCar()
{
    ++carAmount;
}

void
SingleLaneBridge::checkTraffic()
{
    if(downCarsCount > upCarsCount && !(*trafficLightChange)) {
        trafficControler -> setLanePass(true);
    } else if(upCarsCount > downCarsCount && !(*trafficLightChange)) {
        trafficControler -> setLanePass(false);
    }
}
