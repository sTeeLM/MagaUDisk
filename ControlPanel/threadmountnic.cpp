#include "threadmountnic.h"
#include "controlpanelapplication.h"
#include "processcommander.h"

#include <QDebug>

ThreadMountNic::ThreadMountNic(QObject *parent, bool isMount)
    : StateThreadMount(parent, isMount)
{}

void ThreadMountNic::run()
{
    ProcessCommander process;
    QStringList args;
    qDebug() << tr("ThreadMountNic::run ");

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
