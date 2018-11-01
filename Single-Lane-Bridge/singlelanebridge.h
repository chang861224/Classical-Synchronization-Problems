#ifndef SINGLELANEBRIDGE_H
#define SINGLELANEBRIDGE_H

#include <QThread>
#include <QDebug>
#include <QSemaphore>

const int kMaxCars2Pass = 5;
static QSemaphore *eastTrafficLight = new QSemaphore(kMaxCars2Pass);
static QSemaphore *westTrafficLight = new QSemaphore(kMaxCars2Pass);
const int bridgeLen = 1000;
const int bridgeEntryPos[2] = {300, 700};
const int bridgeTurnPos[6] = {0, 300, 400, 600, 700, 1000};

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
};

#endif // SINGLELANEBRIDGE_H
