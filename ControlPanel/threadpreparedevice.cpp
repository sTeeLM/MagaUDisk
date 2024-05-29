#include "threadpreparedevice.h"

ThreadPrepareDevice::ThreadPrepareDevice(QObject *parent)
    :StateThread(parent)
    ,srcDevicePath(tr(""))
    ,dstDevicePath(tr(""))
    ,strPassword(tr(""))
    ,isEncrypted(false)
{

}

void ThreadPrepareDevice::run()
{
    QThread::sleep(5);
    setOK();
    //setFailed(StateThread::WRONG_PASS, QString(tr("密码错误")));
}
