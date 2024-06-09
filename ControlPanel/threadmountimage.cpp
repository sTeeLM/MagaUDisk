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
            /* get block info */
            args.clear();
            args.append(tr("-o"));
            args.append(tr("export"));
            args.append(tr("-p"));
            args.append(fullPath);
            if(!process.oneShot(tr("/usr/sbin/blkid"),args)) {
                setState(SYSTEM_ERROR, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            setBlockInfo(QString::fromLocal8Bit(process.getStdout()));
            process.clean();

            /* setup usb mass storage */
            args.clear();
            args.append(tr("g_mass_storage"));
            args.append(tr("file='%1'").arg(fullPath));
            if(fullPath.lastIndexOf(".iso", -1, Qt::CaseInsensitive) >= 0) {
                args.append(tr("cdrom=1"));
            }
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
            setStateOK();
        }
    }while(0);
    process.clean();
}
