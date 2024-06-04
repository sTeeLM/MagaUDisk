#include "threadmountimage.h"
#include "controlpanelapplication.h"
#include "processcommander.h"

#include <QDebug>

ThreadMountImage::ThreadMountImage(QObject *parent, bool isMount, const QString & image)
    : StateThreadMount(parent, isMount)
    , imagePath(image)
{}

void ThreadMountImage::run()
{
    ProcessCommander process;
    QStringList args;
    qDebug() << tr("ThreadMountImage::run image path is %1").arg(imagePath);

    do {
        if(isMount()) {
            /* setup usb mass storage */
            //args.clear();
            //args.append(tr("/dev/mapper/ControlPanel"));
            //if(!process.oneShot(tr("/usr/sbin/modprobe"),args)) {
            //    setState(SYSTEM_ERROR, process.getLastError());
            //    break;
            //}
            setStateOK();
        } else {
            /* clean usb mass storage */
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
