#ifndef THREADPREPAREDEVICE_H
#define THREADPREPAREDEVICE_H

#include "statethreadbase.h"

#include <QObject>
#include <QThread>

class ThreadPrepareDevice : public StateThreadBase
{
    Q_OBJECT
public:
    explicit ThreadPrepareDevice(QObject *parent, const QString & password);
    void run();
private:
    QString strPassword;

};

#endif // THREADPREPAREDEVICE_H
