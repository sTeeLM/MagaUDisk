#ifndef THREADPREPAREDEVICE_H
#define THREADPREPAREDEVICE_H

#include "statethread.h"

#include <QObject>
#include <QThread>

class ThreadPrepareDevice : public StateThread
{
    Q_OBJECT
public:
    explicit ThreadPrepareDevice(QObject *parent = nullptr);

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

    void setEncrypted(QString & pass) {
        isEncrypted = true;
        strPassword = pass;
    }

    bool isEncryped() {
        return isEncrypted;
    }

private:
    // 分区文件
    QString srcDevicePath;
    // loop设备或者是map设备，取决于是否是加密的
    QString dstDevicePath;
    bool    isEncrypted;
    QString strPassword;
    void run();
};

#endif // THREADPREPAREDEVICE_H
