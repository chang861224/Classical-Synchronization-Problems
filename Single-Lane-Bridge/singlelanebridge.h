#ifndef SINGLELANEBRIDGE_H
#define SINGLELANEBRIDGE_H

#include <QThread>
#include <QDebug>
#include <QSemaphore>

const int kMaxCars2Pass = 3;
static QSemaphore *eastTrafficLight = new QSemaphore(kMaxCars2Pass);
static QSemaphore *westTrafficLight = new QSemaphore(0);
const int bridgeTurnPos[6] = {0, 300, 400, 600, 700, 1000};
const int bridgeLen = bridgeTurnPos[5];
const int bridgeEntryPos = bridgeTurnPos[1];

class SingleLaneBridge : public QThread
{
    Q_OBJECT

public:
    SingleLaneBridge();
    void run();

public slots:
    void updatePos(int carID, int pos);

signals:
    void carChanged(int carID, int pos);
    void deleteCar(int carID);

private:
    bool east2west; // Control which direction's car can go
    void switchLight(); // Switch both traffic light
};

#endif // SINGLELANEBRIDGE_H
