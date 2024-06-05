#ifndef THREADMOUNTPARTATION_H
#define THREADMOUNTPARTATION_H

#include <QObject>
#include "threadblockbase.h"

class ThreadMountPartation : public ThreadBlockBase
{
    Q_OBJECT
public:
    explicit ThreadMountPartation(QObject *parent = nullptr, bool isMount = true);
    void run();
};

#endif // THREADMOUNTPARTATION_H
