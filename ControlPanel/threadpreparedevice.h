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

public:
    void setSrcDevicePath(QString & src) {
        srcDevicePath = src;
    }
    QString & getSrcDevicePath() {
        return srcDevicePath;
    }

    QString & getDstDevicePath() {
        return dstDevicePath;
    }

private:
    // 分区文件
    QString srcDevicePath;
    QString dstDevicePath;
    QString strPassword;
    void run();
};

#endif // THREADPREPAREDEVICE_H
