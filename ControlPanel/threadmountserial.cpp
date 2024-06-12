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
            args.append("g_serial");
            args.append(QString("idVendor=%1").arg(app->config.getIdVendor()));
            args.append(QString("idProduct=%1").arg(app->config.getIdProduct()));
            args.append(QString("bcdDevice=%1").arg(app->config.getBcdDevice()));
            args.append(QString("iManufacturer=%1").arg(app->config.getIManufacturer()));
            args.append(QString("iProduct=%1").arg(app->config.getIProduct()));
            args.append(QString("iSerialNumber=%1").arg(app->config.getISerialNumber()));
            if(!process.oneShot("/usr/sbin/modprobe", args)) {
                setState(MOUNT_SERIAL_FAILED, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();

            /* wait serial ready */
            QThread::sleep(5);

            /* restart serial-gtty */
            args.clear();
            args.append("restart");
            args.append("serial-getty@ttyGS0.service");
            if(!process.oneShot("/usr/bin/systemctl", args)) {
                setState(MOUNT_SERIAL_FAILED, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();
            setStateOK();
        } else {
            /* stop serial-gtty */
            args.clear();
            args.append("stop");
            args.append("serial-getty@ttyGS0.service");
            if(!process.oneShot("/usr/bin/systemctl", args)) {
                setState(UNMOUNT_SERIAL_FAILED, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();
            /* clean usb serial */
            args.clear();
            args.append("g_serial");
            if(!process.oneShot("/usr/sbin/rmmod",args)) {
                setState(UNMOUNT_SERIAL_FAILED, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();
            setStateOK();
        }
    }while(0);
    process.clean();
}
