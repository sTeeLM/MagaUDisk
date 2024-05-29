#ifndef THREADMOUNTNIC_H
#define THREADMOUNTNIC_H

#include <QObject>
#include "statethread.h"

class ThreadMountNic : public StateThread
{
    Q_OBJECT
public:
    explicit ThreadMountNic(QObject *parent = nullptr);
};

#endif // THREADMOUNTNIC_H
