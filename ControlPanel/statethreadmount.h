#ifndef STATETHREADMOUNT_H
#define STATETHREADMOUNT_H

#include <QObject>
#include "statethreadbase.h"

class StateThreadMount : public StateThreadBase
{
    Q_OBJECT
public:
    explicit StateThreadMount(QObject *parent = nullptr, bool isMount = true);

    bool isMount()
    {
        return isMountThread;
    }

private:
    bool isMountThread;
};

#endif // STATETHREADMOUNT_H
