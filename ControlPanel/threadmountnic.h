#ifndef THREADMOUNTNIC_H
#define THREADMOUNTNIC_H

#include <QObject>
#include "statethreadmount.h"
#include "nicitem.h"

class ThreadMountNic : public StateThreadMount
{
    Q_OBJECT
public:
    explicit ThreadMountNic(QObject *parent = nullptr, bool isMount = true, NicItem * item = nullptr, const QString & password = {});
    void run();
private:
    NicItem * nicItem;
    QString password;
};

#endif // THREADMOUNTNIC_H
