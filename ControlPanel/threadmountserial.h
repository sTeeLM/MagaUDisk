#ifndef THREADMOUNTSERIAL_H
#define THREADMOUNTSERIAL_H

#include <QObject>
#include "statethread.h"

class ThreadMountSerial : public StateThread
{
    Q_OBJECT
public:
    explicit ThreadMountSerial(QObject *parent = nullptr);
};

#endif // THREADMOUNTSERIAL_H
