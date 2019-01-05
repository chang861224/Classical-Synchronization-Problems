#include "car.h"
#include <random>

unsigned int Car::lastID = 0;

Car::Car(bool direction, int timeInterval) : id(++lastID)
{
    srand(lastID);

    maxDistance = new int(0);

    // Set direction
    _direction = direction;

    // Set velocity
    if(timeInterval == 0) tickInterval = (5 + rand() % 16);
    else if(timeInterval > 20) tickInterval = 20;
    else if(timeInterval < 5) tickInterval = 5;
    else tickInterval = timeInterval;
    tickInterval += (rand() % 5);

    pos = 0;
}

void
Car::run()
{
    for(pos=1; pos < bridgeLen; ++pos){
        // Wait until there's space to move
        while(pos > (*maxDistance)) QThread::currentThread() -> msleep(100);

        if(pos == bridgeEntryPos) {
            // Wait until bridge ok to go
            while(*disablePass) QThread::currentThread() -> msleep(100);
            while(*rightPass != _direction) QThread::currentThread() -> msleep(100);

            trafficLight->acquire(1);
            emit enterBridge(_direction);
        } else if(pos == (bridgeLen - bridgeEntryPos)) {
            trafficLight->release(1);
        }

        if(_direction == false) emit posChanged(id, pos);
        else if(_direction == true) emit posChanged(id, -pos);
        emit backCarMaxDistance(this, pos);

        QThread::currentThread() -> msleep(tickInterval);
    }

    emit backCarMaxDistance(this, bridgeLen);
    emit finished(id);
}

unsigned int
Car::getID() const
{
    return id;
}

void
Car::setTrafficLight(QSemaphore *tLight)
{
    trafficLight = tLight;

    back = NULL;
}

void
Car::setCarPass(bool *lightChange, bool *rPass)
{
    disablePass = lightChange;
    rightPass = rPass;
}

void
Car::setMaxDistance(int distance)
{
    *maxDistance = distance;
}

bool
Car::getDirection() const
{
    return _direction;
}

void
Car::setBackCar(Car *car)
{
    back = car;
}

Car*
Car::getBackCar() const
{
    return back;
}

int
Car::getPos() const
{
    return pos;
}

