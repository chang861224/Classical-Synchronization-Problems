#include "singlelanebridge.h"
#include "car.h"
#include "trafficcontrol.h"
#include <QSemaphore>

SingleLaneBridge::SingleLaneBridge()
{
    if(eastTrafficLight -> available() > 0) east2west = true;
    else if(westTrafficLight -> available() > 0) east2west = false;

    upCarsCount = 0;
    downCarsCount = 0;

    trafficLightChange = new bool(false);

    carWidth = 60;
    createFreq = 800;
}

void
SingleLaneBridge::run()
{
    for(int iter(0); iter < 50; ++iter){
        Car *tmpCar;
        if(iter %2) {
            tmpCar = new Car(true);
            ++upCarsCount;
        }
        else {
            tmpCar = new Car(false);
            ++downCarsCount;
        }

        tmpCar -> setTrafficLight(westTrafficLight, eastTrafficLight);
        tmpCar -> setCarPass(trafficLightChange);
        cars.insert(std::pair<int, Car*>(tmpCar->getID(), tmpCar));
    }

    trafficControler = new TrafficControl;
    trafficControler -> setCarPass(trafficLightChange);
    trafficControler -> setTrafficLight(westTrafficLight, eastTrafficLight);

    std::map<int, Car*>::iterator iter;
    Car *lastUpCar(NULL), *lastDownCar(NULL);
    for(iter = cars.begin(); iter != cars.end(); ++iter){
        Car *currCar = (iter -> second);
        if(currCar -> getDirection()) {
            if(lastDownCar == NULL) currCar -> setMaxDistance(bridgeLen);
            else {
                lastDownCar -> setBackCar(currCar);
                currCar -> setMaxDistance(lastDownCar->getPos() - carWidth);
            }
        } else {
            if(lastUpCar == NULL) currCar -> setMaxDistance(bridgeLen);
            else {
                lastUpCar -> setBackCar(currCar);
                currCar -> setMaxDistance(lastUpCar->getPos() - carWidth);
            }
        }
        connect(currCar, SIGNAL(backCarMaxDistance(Car*,int)), this, SLOT(updatePos(Car*,int)));

        currCar -> start();
        connect(currCar, SIGNAL(posChanged(int,int)), this, SIGNAL(carChanged(int,int)));
        connect(currCar, SIGNAL(finished()), currCar, SLOT(deleteLater()));
        connect(currCar, SIGNAL(finished(int)), this, SIGNAL(deleteCar(int)));
        connect(currCar, SIGNAL(leaveBridge(bool)), this, SLOT(setFinishCar(bool)));

        if(currCar -> getDirection()) lastDownCar = currCar;
        else lastUpCar = currCar;
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
SingleLaneBridge::setFinishCar(bool direction)
{
    if(direction) {
        --downCarsCount;
        if(upCarsCount > downCarsCount && !(*trafficLightChange)) {
            trafficControler -> setLanePass(!direction);
        }
    }
    else {
        --upCarsCount;
        if(downCarsCount > upCarsCount && !(*trafficLightChange)) {
            trafficControler -> setLanePass(!direction);
        }
    }
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
