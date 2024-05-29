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
    QThread::sleep(10);
    setOK();
}
