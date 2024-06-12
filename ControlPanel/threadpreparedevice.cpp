#include "controlpanelapplication.h"
#include "threadpreparedevice.h"
#include "processcommander.h"

#include <QDebug>
#include <QFile>
#include <QApplication>
#include <QStringList>

ThreadPrepareDevice::ThreadPrepareDevice(QObject *parent, const QString & password, bool isMount)
    :StateThreadMount(parent, isMount)
    ,strPassword(password)
{

}

void ThreadPrepareDevice::run()
{
    ProcessCommander process;
    QStringList args, envs;
    int retVal, exCode = -1;
    QString stderr;
    ControlPanelApplication * app = qobject_cast<ControlPanelApplication *>(qApp);

    envs.append("PATH=/bin:/usr/bin:/sbin/usr/sbin");

    if(isMount()) {
        do {
            /* close vtcon */
            args.clear();
            args.append("-c");
            args.append("echo 0 > /sys/class/vtconsole/vtcon1/bind");
            process.oneShot("/usr/bin/sh", args);
            process.clean();

            /* umount mount point if nessaery */
            args.clear();
            args.append("/dev/mapper/ControlPanel");
            args.append("/proc/mounts");
            if(process.oneShot("/usr/bin/grep", args)) {
                qDebug() << tr("ThreadPrepareDevice::run /dev/mapper/ControlPanel already mounted, try unmount it!");
                args.clear();
                args.append("/dev/mapper/ControlPanel");
                if(!process.oneShot("/usr/bin/umount",args)) {
                    setState(SYSTEM_ERROR, process.getLastError());
                    break;
                }
            }
            process.clean();

            args.clear();
            args.append("/dev/mapper/ControlPanel");
            if(process.oneShot("/bin/ls", args)) {
                qDebug() << tr("ThreadPrepareDevice::run /dev/mapper/ControlPanel exist, try close it!");
                args.clear();
                args.append("close");
                args.append("ControlPanel");
                if(!process.oneShot("/usr/sbin/cryptsetup", args)) {
                    setState(SYSTEM_ERROR, process.getLastError());
                    break;
                }
            }
            process.clean();

            /* open device with password */
            process.setProgram("/usr/sbin/cryptsetup");
            args.clear();
            args.append("open");
            args.append(app->config.getSourcePartation());
            args.append("ControlPanel");
            process.setArguments(args);
            process.setEnvironment(envs);
            if(!process.start()) {
                setState(SYSTEM_ERROR, process.getLastError());
                break;
            }

            process.writeStdin(strPassword.append("\n").toLocal8Bit());
            stderr = "No key available with this passphrase\\.\\n$";
            retVal = process.waitForConditions({}, stderr, WAIT_MASK_STDERR|WAIT_MASK_STATUS,
                                               app->config.getCommandTimeoutMs());

            if(retVal & WAIT_MASK_STDERR) {
                setState(WRONG_PASS, QString(process.getStderr()));
                break;
            }

            if(!(retVal & WAIT_MASK_STATUS) || !process.isExited(&exCode) || exCode != 0) {
                setState(SYSTEM_ERROR, QString(process.getStderr()));
                break;
            }
            process.clean();

            /* mount it to mount_root */
            args.clear();
            args.append("-o");
            args.append("rw");
            args.append("/dev/mapper/ControlPanel");
            args.append(app->config.getMountRoot());
            if(process.oneShot("/usr/bin/mount",args)) {
                setStateOK();
                break;
            } else {
                setState(SYSTEM_ERROR, QString(process.getStderr()));
                break;
            }
        }while(0);
        process.clean();
    } else {
        do {
            /* unmount */
            args.clear();
            args.append("/dev/mapper/ControlPanel");
            process.setArguments(args);
            if(!process.oneShot("/usr/bin/umount", args)) {
                setState(SYSTEM_ERROR, process.getLastError());
                break;
            }
            /* close device */
            args.clear();
            args.append("close");
            args.append("/dev/mapper/ControlPanel");
            process.setArguments(args);
            if(!process.oneShot("/usr/sbin/cryptsetup", args)) {
                setState(SYSTEM_ERROR, process.getLastError());
                break;
            }

            setStateOK();
        }while(0);
        process.clean();
    }
}
