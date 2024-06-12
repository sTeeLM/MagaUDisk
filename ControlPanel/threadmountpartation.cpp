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

    qDebug() << tr("ThreadMountPartation::run isMount is %1").arg(isMount());

    do {
        if(isMount()) {
            /* umount mount root */
            args.clear();
            args.append("/dev/mapper/ControlPanel");
            if(!process.oneShot("/usr/bin/umount",args)) {
                setState(MOUNT_PART_FAILED, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();

            /* get block info */
            args.clear();
            args.append("-o");
            args.append("export");
            args.append("-p");
            args.append("/dev/mapper/ControlPanel");
            if(!process.oneShot(tr("/usr/sbin/blkid"),args)) {
                setState(MOUNT_PART_FAILED, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            setBlockInfo(QString::fromLocal8Bit(process.getStdout()));
            process.clean();

            /* setup usb mass storage */
            args.clear();
            args.append("g_mass_storage");
            args.append("file=/dev/mapper/ControlPanel");
            args.append(QString("removable=1"));
            args.append(QString("idVendor=%1").arg(app->config.getIdVendor()));
            args.append(QString("idProduct=%1").arg(app->config.getIdProduct()));
            args.append(QString("bcdDevice=%1").arg(app->config.getBcdDevice()));
            args.append(QString("iManufacturer=%1").arg(app->config.getIManufacturer()));
            args.append(QString("iProduct=%1").arg(app->config.getIProduct()));
            args.append(QString("iSerialNumber=%1").arg(app->config.getISerialNumber()));
            if(!process.oneShot("/usr/sbin/modprobe", args)) {
                setState(MOUNT_PART_FAILED, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();
            setStateOK();
        } else {
            /* clean usb mass storage */
            args.clear();
            args.append("g_mass_storage");
            if(!process.oneShot("/usr/sbin/rmmod",args)) {
                setState(UNMOUNT_PART_FAILED, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();
            /* mount root */
            args.clear();
            args.append("-o");
            args.append("rw");
            args.append("/dev/mapper/ControlPanel");
            args.append(app->config.getMountRoot());
            if(!process.oneShot("/usr/bin/mount",args)) {
                setState(UNMOUNT_PART_FAILED, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();
            setStateOK();
        }
    }while(0);
    process.clean();
}
