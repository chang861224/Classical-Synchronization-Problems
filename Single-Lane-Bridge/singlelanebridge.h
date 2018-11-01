#ifndef SINGLELANEBRIDGE_H
#define SINGLELANEBRIDGE_H

#include <QThread>
#include <QDebug>
#include <QSemaphore>

const int kMaxCars2Pass = 5;
static QSemaphore *eastTrafficLight = new QSemaphore(kMaxCars2Pass);
static QSemaphore *westTrafficLight = new QSemaphore(kMaxCars2Pass);

class SingleLaneBridge : public QThread
{
    Q_OBJECT

public:
    SingleLaneBridge();
    void run();

public slots:
    void updatePos(int carID, int pos);

protected:
    int bridgeLen;
    int bridgeEntryPos[2];
};

#endif // SINGLELANEBRIDGE_H
