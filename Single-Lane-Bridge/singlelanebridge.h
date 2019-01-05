#ifndef SINGLELANEBRIDGE_H
#define SINGLELANEBRIDGE_H

#include <QThread>
#include <QDebug>
#include <QSemaphore>
#include <map>
class Car;
class TrafficControl;

const int kMaxCars2Pass = 3;
const int bridgeTurnPos[6] = {0, 150, 200, 300, 350, 500};
const int bridgeLen = bridgeTurnPos[5];
const int bridgeEntryPos = bridgeTurnPos[1];

class SingleLaneBridge : public QThread
{
    Q_OBJECT

public:
    SingleLaneBridge();
    void run();
    int carWidth;

public slots:
    void updatePos(Car *car, int pos);
    void setEnterCar(bool direction);
    void setCarWidth(int width);
    void checkTraffic();
    void init();
    void setCreateFreq(int ms);
    void setCarSpeed(int speed);
    void createCar();
    void autoCreateCar();

signals:
    void carChanged(int carID, int pos);
    void deleteCar(int carID);

private:
    // No more car can enter the bridge if true
    bool *trafficLightChange;
    bool *rightPass;
    QSemaphore *trafficLight = new QSemaphore(kMaxCars2Pass);

    int upCarsCount;
    int downCarsCount;
    TrafficControl *trafficControler;
    int createFreq;
    int carSpeed;
    int carAmount;
};

#endif // SINGLELANEBRIDGE_H
