#include "threadmountpartation.h"
#include "controlpanelapplication.h"
#include "processcommander.h"

#include <QDebug>
#include <QFile>
#include <QApplication>
#include <QStringList>

ThreadMountPartation::ThreadMountPartation(QObject *parent, bool isMount)
    : ThreadBlockBase(parent, isMount)
{}

void ThreadMountPartation::run()
{
    ProcessCommander process;
    QStringList args;
    QString stdoutStr;
    ControlPanelApplication * app = qobject_cast<ControlPanelApplication *>(qApp);

    do {
        if(isMount()) {
            /* umount mount root */
            args.clear();
            args.append(tr("/dev/mapper/ControlPanel"));
            if(!process.oneShot(tr("/usr/bin/umount"),args)) {
                setState(SYSTEM_ERROR, process.getLastError());
                break;
            }
            process.clean();

            /* get block info */
            args.clear();
            args.append(tr("-o"));
            args.append(tr("export"));
            args.append(tr("-p"));
            args.append(tr("/dev/mapper/ControlPanel"));
            if(!process.oneShot(tr("/usr/sbin/blkid"),args)) {
                setState(SYSTEM_ERROR, process.getLastError());
                break;
            }
            setBlockInfo(QString::fromLocal8Bit(process.getStdout()));
            process.clean();

            /* setup usb mass storage */
            //args.clear();
            //args.append(tr("/dev/mapper/ControlPanel"));
            //if(!process.oneShot(tr("/usr/sbin/modprobe"),args)) {
            //    setState(SYSTEM_ERROR, process.getLastError());
            //    break;
            //}
            process.clean();
            setStateOK();
        } else {
            /* clean usb mass storage */
            //args.clear();
            //args.append(tr("/dev/mapper/ControlPanel"));
            //if(!process.oneShot(tr("/usr/sbin/rmmod"),args)) {
            //    setState(SYSTEM_ERROR, process.getLastError());
            //    break;
            //}
            //process.clean();
            /* mount root */
            args.clear();
            args.append(tr("-o"));
            args.append(tr("rw"));
            args.append(tr("/dev/mapper/ControlPanel"));
            args.append(app->config.getMountRoot());
            if(!process.oneShot(tr("/usr/bin/mount"),args)) {
                setState(SYSTEM_ERROR, process.getLastError());
                break;
            }
            process.clean();
            setStateOK();
        }
    }while(0);
    process.clean();
}
