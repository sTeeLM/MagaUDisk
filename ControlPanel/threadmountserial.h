#ifndef THREADMOUNTSERIAL_H
#define THREADMOUNTSERIAL_H

#include <QObject>
#include "statethreadmount.h"

class ThreadMountSerial : public StateThreadMount
{
    Q_OBJECT
public:
    explicit ThreadMountSerial(QObject *parent = nullptr, bool isMount = true);
};

#endif // THREADMOUNTSERIAL_H
