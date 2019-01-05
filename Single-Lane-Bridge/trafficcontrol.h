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
    QSemaphore *trafficLight;
    bool *disablePass;
    bool *rightPass;
    void setLanePass(bool direction);

public slots:
    void setTrafficLight(QSemaphore *tLight);
    void setCarPass(bool *lightChange, bool *rPass);

private:
};

#endif // TRAFFICCONTROL_H
