#include "threadmountserial.h"
#include "controlpanelapplication.h"
#include "processcommander.h"

#include <QDebug>
ThreadMountSerial::ThreadMountSerial(QObject *parent, bool isMount)
    : StateThreadMount(parent, isMount)
{}


void ThreadMountSerial::run()
{
    ProcessCommander process;
    QStringList args;

    qDebug() << tr("ThreadMountSerial::run ");

    do {
        if(isMount()) {
            /* setup usb nic */
            //args.clear();
            //args.append(tr("/dev/mapper/ControlPanel"));
            //if(!process.oneShot(tr("/usr/sbin/modprobe"),args)) {
            //    setState(SYSTEM_ERROR, process.getLastError());
            //    break;
            //}
            setStateOK();
        } else {
            /* clean usb nic */
            //args.clear();
            //args.append(tr("/dev/mapper/ControlPanel"));
            //if(!process.oneShot(tr("/usr/sbin/rmmod"),args)) {
            //    setState(SYSTEM_ERROR, process.getLastError());
            //    break;
            //}
            setStateOK();
        }
    }while(0);
    process.clean();
}
