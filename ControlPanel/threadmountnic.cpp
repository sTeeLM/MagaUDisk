#include "threadmountnic.h"
#include "controlpanelapplication.h"
#include "processcommander.h"

#include <QDebug>

ThreadMountNic::ThreadMountNic(QObject *parent, bool isMount, NicItem * item, const QString & pass)
    : StateThreadMount(parent, isMount)
    , nicItem(item)
    , password(pass)
{}

void ThreadMountNic::run()
{
    ProcessCommander process;
    ControlPanelApplication * app = qobject_cast<ControlPanelApplication *>(qApp);
    QStringList args, envs;
    if(nicItem)
        qDebug() << tr("ThreadMountNic::run, nic is %1, pass is %2, isMount is %3").arg(nicItem->getSsid()).arg(password).arg(isMount());
    else
        qDebug() << tr("ThreadMountNic::run, isMount is %3").arg(isMount());
    /*
    wifi connect (B)SSID [password password] [wep-key-type {key | phrase}] [ifname ifname]
       [bssid BSSID] [name name] [private {yes | no}] [hidden {yes | no}]
    */
    envs.append("PATH=/bin:/usr/bin:/sbin/usr/sbin");
    envs.append("LANG=zh_CN.UTF-8");
    do {
        if(isMount()) {
            /* connect to wifi */
            args.append("device");
            args.append("wifi");
            args.append("connect");
            args.append(nicItem->getSsid());
            args.append("password");
            args.append(password);
            args.append("bssid");
            args.append(nicItem->getBssid());
            args.append("name");
            args.append("ControlPanel");
            if(!process.oneShot("/usr/bin/nmcli", args, envs)) {
                qDebug() << tr("connect to wifi failed");
                setState(MOUNT_NIC_FAILED, process.getLastError());
                break;
            }
            process.clean();

            /* setup usb nic */
            args.clear();
            args.append("g_ether");
            args.append(QString("idVendor=%1").arg(app->config.getIdVendor()));
            args.append(QString("idProduct=%1").arg(app->config.getIdProduct()));
            args.append(QString("bcdDevice=%1").arg(app->config.getBcdDevice()));
            args.append(QString("iManufacturer=%1").arg(app->config.getIManufacturer()));
            args.append(QString("iProduct=%1").arg(app->config.getIProduct()));
            args.append(QString("iSerialNumber=%1").arg(app->config.getISerialNumber()));
            if(!process.oneShot("/usr/sbin/modprobe", args)) {
                qDebug() << tr("install usb0 failed");
                setState(MOUNT_NIC_FAILED, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();

            QThread::sleep(5);

            /* up usb0 */
            args.clear();
            args.append("connection");
            args.append("up");
            args.append("usb0");
            if(!process.oneShot("/usr/bin/nmcli", args, envs)) {
                qDebug() << tr("up usb0 failed");
                setState(MOUNT_NIC_FAILED, process.getLastError());
                break;
            }
            process.clean();

            /* restart iptables */
            args.clear();
            args.append("restart");
            args.append("iptables.service");
            if(!process.oneShot("/usr/bin/systemctl", args)) {
                qDebug() << tr("iptables restart failed");
                setState(MOUNT_NIC_FAILED, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();

            /* restart dnsmasq */
            args.clear();
            args.append("restart");
            args.append("dnsmasq.service");
            if(!process.oneShot("/usr/bin/systemctl", args)) {
                qDebug() << tr("dnsmasq restart failed");
                setState(MOUNT_NIC_FAILED, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();

            setStateOK();
        } else {
            /* down usb0 */
            args.clear();
            args.append("connection");
            args.append("down");
            args.append("usb0");
            if(!process.oneShot("/usr/bin/nmcli", args, envs)) {
                setState(UNMOUNT_NIC_FAILED, process.getLastError());
                break;
            }
            process.clean();

            /* clean usb nic */
            args.clear();
            args.append("g_ether");
            if(!process.oneShot("/usr/sbin/rmmod", args)) {
                setState(UNMOUNT_NIC_FAILED, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();
            setStateOK();
        }
    }while(0);
    process.clean();
}
