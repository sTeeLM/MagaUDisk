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
    ControlPanelApplication * app = qobject_cast<ControlPanelApplication *>(qApp);
    QStringList args;

    qDebug() << tr("ThreadMountSerial::run isMount is %1").arg(isMount());

    do {
        if(isMount()) {
            /* setup usb serial */
            args.clear();
            args.append(tr("g_serial"));
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

            /* restart serial-gtty */
            args.clear();
            args.append(tr("restart"));
            args.append(tr("serial-getty@ttyGS0.service"));
            if(!process.oneShot(tr("/usr/bin/systemctl"), args)) {
                setState(SYSTEM_ERROR, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();
            setStateOK();
        } else {
            /* clean usb serial */
            args.clear();
            args.append(tr("g_serial"));
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
