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
    if(timeInterval == 0) tickInterval = (7 + rand() % 7);
    else if(timeInterval > 13) tickInterval = 13;
    else if(timeInterval < 7) tickInterval = 7;
    else tickInterval = timeInterval;

    pos = 0;
}

void
Car::run()
{
    for(pos=1; pos < bridgeLen; ++pos){
        while(pos > (*maxDistance)) QThread::currentThread() -> msleep(100);

        if(pos == bridgeEntryPos) {
            while(*disablePass) QThread::currentThread() -> msleep(100);
            if(_direction == false) {
                lTrafficLight -> acquire(1);
            }
            else if(_direction == true) {
                rTrafficLight -> acquire(1);
            }
        } else if(pos == (bridgeLen - bridgeEntryPos)) {
            if(_direction == false) lTrafficLight -> release(1);
            else if(_direction == true) rTrafficLight -> release(1);

            emit leaveBridge(_direction);
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
Car::setTrafficLight(QSemaphore *left, QSemaphore *right)
{
    lTrafficLight = left;
    rTrafficLight = right;

    back = NULL;
}

void
Car::setCarPass(bool *lightChange)
{
    disablePass = lightChange;
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

