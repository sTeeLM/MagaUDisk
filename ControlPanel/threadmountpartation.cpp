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
            args.append(tr("/dev/mapper/ControlPanel"));
            if(!process.oneShot(tr("/usr/bin/umount"),args)) {
                setState(SYSTEM_ERROR, QString::fromLocal8Bit(process.getStderr()));
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
                setState(SYSTEM_ERROR, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            setBlockInfo(QString::fromLocal8Bit(process.getStdout()));
            process.clean();

            /* setup usb mass storage */
            args.clear();
            args.append(tr("g_mass_storage"));
            args.append(tr("file=/dev/mapper/ControlPanel"));
            args.append(tr("removable=1"));
            args.append(tr("idVendor=%1").arg(app->config.getIdVendor()));
            args.append(tr("idProduc=%1").arg(app->config.getIdProduct()));
            args.append(tr("bcdDevice=%1").arg(app->config.getBcdDevice()));
            args.append(tr("iManufacturer=%1").arg(app->config.getIManufacturer()));
            args.append(tr("iProduct=%1").arg(app->config.getIProduct()));
            args.append(tr("iSerialNumber=%1").arg(app->config.getISerialNumber()));
            if(!process.oneShot(tr("/usr/sbin/modprobe"), args)) {
                setState(SYSTEM_ERROR, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();
            setStateOK();
        } else {
            /* clean usb mass storage */
            args.clear();
            args.append(tr("g_mass_storage"));
            if(!process.oneShot(tr("/usr/sbin/rmmod"),args)) {
                setState(SYSTEM_ERROR, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();
            /* mount root */
            args.clear();
            args.append(tr("-o"));
            args.append(tr("rw"));
            args.append(tr("/dev/mapper/ControlPanel"));
            args.append(app->config.getMountRoot());
            if(!process.oneShot(tr("/usr/bin/mount"),args)) {
                setState(SYSTEM_ERROR, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();
            setStateOK();
        }
    }while(0);
    process.clean();
}
