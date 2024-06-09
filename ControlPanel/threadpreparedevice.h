#ifndef THREADPREPAREDEVICE_H
#define THREADPREPAREDEVICE_H

#include "statethreadmount.h"

#include <QObject>
#include <QThread>

class ThreadPrepareDevice : public StateThreadMount
{
    Q_OBJECT
public:
    explicit ThreadPrepareDevice(QObject *parent, const QString & password, bool isMount = true);
    void run();
private:
    QString strPassword;

};

#endif // THREADPREPAREDEVICE_H
