#include "car.h"
#include <random>

unsigned int Car::lastID = 0;

Car::Car(bool direction, int speed) : id(++lastID)
{
    srand(lastID);

    // Set direction
    _direction = direction;

    // Set velocity
    if(speed == 0) velocity = (1 + rand() % 19);
    else if(speed > 20) velocity = 20;
    else if(speed < 0) velocity = 1;
    else velocity = speed;
}

void
Car::run()
{
    qDebug() << &eastTrafficLight;
    for(int pos(1); pos < bridgeLen; ++pos){
        if(pos == bridgeEntryPos) {
            if(_direction == false) {
                westTrafficLight -> acquire(1);
            }
            else if(_direction == true) {
                eastTrafficLight -> acquire(1);
            }
        } else if(pos == (bridgeLen - bridgeEntryPos)) {
            if(_direction == false) westTrafficLight -> release(1);
            else if(_direction == true) eastTrafficLight -> release(1);
        }

        if(_direction == false) emit posChanged(id, pos);
        else if(_direction == true) emit posChanged(id, -pos);
        QThread::currentThread() -> msleep(10);
    }

    emit finished(id);
}

unsigned int
Car::getID() const
{
    return id;
}
