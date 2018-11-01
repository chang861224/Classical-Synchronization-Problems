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
    for(int pos(0); pos < bridgeLen; pos++){
        if(_direction == 0) {
            if(pos == bridgeEntryPos[0]) {
                westTrafficLight -> acquire(1);
            } else if(pos == bridgeEntryPos[1]) {
                westTrafficLight -> release(1);
            }
        } else if(_direction == 1) {
            if(pos == bridgeEntryPos[1]) {
                eastTrafficLight -> acquire(1);
            } else if(pos == bridgeEntryPos[0]) {
                eastTrafficLight -> release(1);
            }
        }

        emit posChanged(id, pos);
        QThread::currentThread() -> msleep(10);
    }
}

unsigned int
Car::getID() const
{
    return id;
}
