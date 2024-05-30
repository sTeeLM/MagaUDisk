#include "threadpreparedevice.h"

ThreadPrepareDevice::ThreadPrepareDevice(QObject *parent, const QString & password)
    :StateThreadBase(parent)
    ,srcDevicePath(tr(""))
    ,dstDevicePath(tr(""))
    ,strPassword(password)
{

}

void ThreadPrepareDevice::run()
{
    QThread::sleep(5);
    setStateOK();
    //setFailed(StateThread::WRONG_PASS, QString(tr("密码错误")));
}
