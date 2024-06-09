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
    qDebug() << tr("ThreadMountNic::run, nic is %1, pass is %2, isMount is %3").arg(nicItem->getSsid()).arg(password).arg(isMount());
    /*
    wifi connect (B)SSID [password password] [wep-key-type {key | phrase}] [ifname ifname]
       [bssid BSSID] [name name] [private {yes | no}] [hidden {yes | no}]
    */
    envs.append(tr("PATH=/bin:/usr/bin:/sbin/usr/sbin"));
    envs.append(tr("LANG=zh_CN.UTF-8"));
    do {
        if(isMount()) {
            /* connect to wifi */
            args.append(tr("wifi"));
            args.append(tr("connect"));
            args.append(tr("%1").arg(nicItem->getSsid()));
            args.append(tr("password"));
            args.append(tr("%1").arg(password));
            args.append(tr("bssid"));
            args.append(tr("%1").arg(nicItem->getBssid()));
            args.append(tr("name"));
            args.append(tr("ControlPanel"));
            if(!process.oneShot(tr("/usr/bin/nmcli"), args, envs)) {
                setState(SYSTEM_ERROR, process.getLastError());
                break;
            }
            process.clean();

            /* setup usb nic */
            args.clear();
            args.append(tr("g_ether"));
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

            /* up usb0 */
            args.clear();
            args.append(tr("connection"));
            args.append(tr("up"));
            args.append(tr("usb0"));
            if(!process.oneShot(tr("/usr/bin/nmcli"), args, envs)) {
                setState(SYSTEM_ERROR, process.getLastError());
                break;
            }
            process.clean();

            /* restart iptables */
            args.clear();
            args.append(tr("restart"));
            args.append(tr("iptables.service"));
            if(!process.oneShot(tr("/usr/bin/systemctl"), args)) {
                setState(SYSTEM_ERROR, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();

            /* restart dnsmasq */
            args.clear();
            args.append(tr("restart"));
            args.append(tr("dnsmasq.service"));
            if(!process.oneShot(tr("/usr/bin/systemctl"), args)) {
                setState(SYSTEM_ERROR, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();

            setStateOK();
        } else {
            /* clean usb nic */
            args.clear();
            args.append(tr("g_ether"));
            if(!process.oneShot(tr("/usr/sbin/rmmod"), args)) {
                setState(SYSTEM_ERROR, QString::fromLocal8Bit(process.getStderr()));
                break;
            }
            process.clean();
            setStateOK();
        }
    }while(0);
    process.clean();
}
