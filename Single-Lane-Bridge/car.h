#ifndef MYTHREADS_H
#define MYTHREADS_H

#include <QThread>
#include <QDebug>
#include <QSemaphore>
#include "singlelanebridge.h"

class Car : public SingleLaneBridge
{
    Q_OBJECT

public:
    Car(bool direction=0, int speed=0);
    void run();
    unsigned int getID() const;
    QSemaphore *lTrafficLight;
    QSemaphore *rTrafficLight;

signals:
    void posChanged(int, int);
    void finished(int);
    void leaveBridge(bool);

public slots:
    void setTrafficLight(QSemaphore *left, QSemaphore *right);
    void setCarPass(bool *lightChange);

private:
    unsigned int id;
    int velocity;
    static unsigned int lastID;
    bool _direction; // 0 for left to right, 1 for right to left
    bool *disablePass;
};

#endif // MYTHREADS_H
