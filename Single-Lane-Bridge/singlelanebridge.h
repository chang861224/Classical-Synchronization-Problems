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
    bool east2west; // Control which direction's car can go
    int carWidth;

public slots:
    void updatePos(Car *car, int pos);
    void setFinishCar(bool direction);
    void setCarWidth(int width);

signals:
    void carChanged(int carID, int pos);
    void deleteCar(int carID);

public slots:
    void init();
    void setCreateFreq(int ms);
    void createCar();

private:
    bool *trafficLightChange;
    QSemaphore *eastTrafficLight = new QSemaphore(kMaxCars2Pass);
    QSemaphore *westTrafficLight = new QSemaphore(0);

    int upCarsCount;
    int downCarsCount;
    TrafficControl *trafficControler;
    int createFreq;
    int carAmount;
};

#endif // SINGLELANEBRIDGE_H
