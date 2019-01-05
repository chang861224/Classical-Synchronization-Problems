#include "singlelanebridge.h"
#include "car.h"
#include "trafficcontrol.h"
#include <QSemaphore>
#include <QTimer>

SingleLaneBridge::SingleLaneBridge()
{
    upCarsCount = 0;
    downCarsCount = 0;
    trafficLightChange = new bool(false);
    rightPass = new bool(false);
    carWidth = 60;
    createFreq = 800;
    carSpeed = 8;
    carAmount = 0;

    QTimer *timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(checkTraffic()));
    timer -> start(1000);
}

void
SingleLaneBridge::run()
{
    trafficControler = new TrafficControl;
    trafficControler -> setCarPass(trafficLightChange, rightPass);
    trafficControler -> setTrafficLight(trafficLight);

    Car *lastUpCar(NULL), *lastDownCar(NULL), *currCar;
    for(int iter(0); iter < INT_MAX; ++iter) {
        // Increase {carAmount} to make more cars
        while(iter >= carAmount) {
            if(carAmount == -1) carAmount = iter;
            QThread::currentThread() -> msleep(100);
        }

        if(iter % 2) {
            currCar = new Car(true, 15 / carSpeed);
            ++downCarsCount;
        } else {
            currCar = new Car(false, 15 / carSpeed);
            ++upCarsCount;
        }
        currCar -> setTrafficLight(trafficLight);
        currCar -> setCarPass(trafficLightChange, rightPass);

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
        trafficControler -> setLanePass(false);
    } else if(upCarsCount > downCarsCount && !(*trafficLightChange)) {
        trafficControler -> setLanePass(true);
    }
}

void
SingleLaneBridge::autoCreateCar()
{
    if(carAmount == INT_MAX) carAmount = -1;
    else carAmount = INT_MAX;
}

void
SingleLaneBridge::setCarSpeed(int speed)
{
    carSpeed = speed / 100;
}
