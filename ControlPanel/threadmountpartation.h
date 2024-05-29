#ifndef THREADMOUNTPARTATION_H
#define THREADMOUNTPARTATION_H

#include <QObject>
#include "statethread.h"

class ThreadMountPartation : public StateThread
{
    Q_OBJECT
public:
    explicit ThreadMountPartation(QObject *parent = nullptr);
};

#endif // THREADMOUNTPARTATION_H
