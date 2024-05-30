#ifndef THREADMOUNTPARTATION_H
#define THREADMOUNTPARTATION_H

#include <QObject>
#include "statethreadmount.h"

class ThreadMountPartation : public StateThreadMount
{
    Q_OBJECT
public:
    explicit ThreadMountPartation(QObject *parent = nullptr, bool isMount = true);
};

#endif // THREADMOUNTPARTATION_H
