#include "trafficcontrol.h"

TrafficControl::TrafficControl()
{
}

void
TrafficControl::run()
{
    if(!(*disablePass)){
        (*disablePass) = true;

        if(east2west){
            rTrafficLight -> acquire(kMaxCars2Pass);
            lTrafficLight -> release(kMaxCars2Pass);
            east2west = false;
        } else {
            lTrafficLight -> acquire(kMaxCars2Pass);
            rTrafficLight -> release(kMaxCars2Pass);
            east2west = true;
        }

        (*disablePass) = false;
    }
}

void
TrafficControl::setTrafficLight(QSemaphore *left, QSemaphore *right)
{
    lTrafficLight = left;
    rTrafficLight = right;
}

void
TrafficControl::setCarPass(bool *lightChange)
{
    disablePass = lightChange;
}

void
TrafficControl::setLanePass(bool direction)
{
    if(east2west != direction){
        this -> start();
    }
}
