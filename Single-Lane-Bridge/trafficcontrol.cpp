#include "trafficcontrol.h"

TrafficControl::TrafficControl()
{
}

void
TrafficControl::run()
{
    if(!(*disablePass)){
        (*disablePass) = true;

        // Wait until there's no car on bridge
        trafficLight -> acquire(kMaxCars2Pass);

        if(*rightPass) {
            *rightPass = false;
        }
        else {
            *rightPass = true;
        }
        trafficLight -> release(kMaxCars2Pass);

        (*disablePass) = false;
    }
}

void
TrafficControl::setTrafficLight(QSemaphore *tlight)
{
    trafficLight = tlight;
}

void
TrafficControl::setCarPass(bool *lightChange, bool *rPass)
{
    disablePass = lightChange;
    rightPass = rPass;
}

void
TrafficControl::setLanePass(bool direction)
{
    if(*rightPass == direction){
        this -> start();
    }
}
