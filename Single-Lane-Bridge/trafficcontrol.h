#ifndef TRAFFICCONTROL_H
#define TRAFFICCONTROL_H

#include <QThread>
#include "singlelanebridge.h"

class TrafficControl : public SingleLaneBridge
{
    Q_OBJECT

public:
    TrafficControl();
    void run();
    QSemaphore *lTrafficLight;
    QSemaphore *rTrafficLight;
    bool *disablePass;
    void setLanePass(bool direction);

public slots:
    void setTrafficLight(QSemaphore *left, QSemaphore *right);
    void setCarPass(bool *lightChange);

private:
};

#endif // TRAFFICCONTROL_H
