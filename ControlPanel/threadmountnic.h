#ifndef THREADMOUNTNIC_H
#define THREADMOUNTNIC_H

#include <QObject>
#include "statethreadmount.h"

class ThreadMountNic : public StateThreadMount
{
    Q_OBJECT
public:
    explicit ThreadMountNic(QObject *parent = nullptr, bool isMount = true);
    void run();
};

#endif // THREADMOUNTNIC_H
