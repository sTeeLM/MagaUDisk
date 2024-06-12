#include "threadmountimage.h"
#include "controlpanelapplication.h"
#include "processcommander.h"

#include <QDebug>

ThreadMountImage::ThreadMountImage(QObject *parent, bool isMount, const QString & image)
    : ThreadBlockBase(parent, isMount)
    , imagePath(image)
{}

void ThreadMountImage::run()
{
    ProcessCommander process;
    ControlPanelApplication * app = qobject_cast<ControlPanelApplication *>(qApp);
    QStringList args;
    QString fullPath = app->config.getMountRoot();
    if(fullPath.right(1) == tr("/")) {
        fullPath.chop(1);
    }
    fullPath += imagePath;
    qDebug() << tr("ThreadMountImage::run list path is %1").arg(fullPath);
    do {
        if(isMount()) {
            int excode;
            /* get block info */
            args.clear();
            args.append("-o");
            args.append("export");
            args.append("-p");
            args.append(fullPath);
            if(!process.oneShot("/usr/sbin/blkid", args, {}, {}, &excode)) {
                if(excode != 2) {
                    setState(MOUNT_IMAGE_FAILED, QString::fromLocal8Bit(process.getStderr()));
                    break;
                }
            }
            setBlockInfo(QString::fromLocal8Bit(process.getStdout()));
            process.clean();

            /* setup usb mass storage */
            args.clear();
            args.append("g_mass_storage");
            args.append(QString("file=%1").arg(fullPath));
            if(fullPath.lastIndexOf(".iso", -1, Qt::CaseInsensitive) >= 0) {
                args.append("cdrom=1");
            }
            args.append(QString("removable=1"));
            args.append(QString("idVendor=%1").arg(app->config.getIdVendor()));
            args.append(QString("idProduct=%1").arg(app->config.getIdProduct()));
            args.append(QString("bcdDevice=%1").arg(app->config.getBcdDevice()));
            args.append(QString("iManufacturer=%1").arg(app->config.getIManufacturer()));
            args.append(QString("iProduct=%1").arg(app->config.getIProduct()));
            args.append(QString("iSerialNumber=%1").arg(app->config.getISerialNumber()));
            if(!process.oneShot(QString("/usr/sbin/modprobe"), args)) {
                setState(MOUNT_IMAGE_FAILED, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();
            setStateOK();
        } else {
            /* clean usb mass storage */
            args.clear();
            args.append("g_mass_storage");
            if(!process.oneShot("/usr/sbin/rmmod",args)) {
                setState(UNMOUNT_IMAGE_FAILED, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();
            setStateOK();
        }
    }while(0);
    process.clean();
}
