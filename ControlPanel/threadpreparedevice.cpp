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

    envs.append(tr("PATH=/bin:/usr/bin:/sbin/usr/sbin"));

    if(isMount()) {
        do {
            /* umount mount point if nessaery */
            args.append(tr("/dev/mapper/ControlPanel"));
            args.append(tr("/proc/mounts"));
            if(process.oneShot(tr("/usr/bin/grep"), args)) {
                qDebug() << tr("ThreadPrepareDevice::run /dev/mapper/ControlPanel already mounted, try unmount it!");
                args.clear();
                args.append(tr("/dev/mapper/ControlPanel"));
                if(!process.oneShot(tr("/usr/bin/umount"),args)) {
                    setState(SYSTEM_ERROR, process.getLastError());
                    break;
                }
            }
            process.clean();

            args.clear();
            args.append(tr("/dev/mapper/ControlPanel"));
            if(process.oneShot(tr("/bin/ls"), args)) {
                qDebug() << tr("ThreadPrepareDevice::run /dev/mapper/ControlPanel exist, try close it!");
                args.clear();
                args.append(tr("close"));
                args.append(tr("ControlPanel"));
                if(!process.oneShot(tr("/usr/sbin/cryptsetup"), args)) {
                    setState(SYSTEM_ERROR, process.getLastError());
                    break;
                }
            }
            process.clean();

            /* open device with password */
            process.setProgram(tr("/usr/sbin/cryptsetup"));
            args.clear();
            args.append(tr("open"));
            args.append(app->config.getSourcePartation());
            args.append(tr("ControlPanel"));
            process.setArguments(args);
            process.setEnvironment(envs);
            if(!process.start()) {
                setState(SYSTEM_ERROR, process.getLastError());
                break;
            }

            process.writeStdin(strPassword.append("\n").toLocal8Bit());
            stderr = tr("No key available with this passphrase\\.\\n$");
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
            args.append(tr("-o"));
            args.append(tr("rw"));
            args.append(tr("/dev/mapper/ControlPanel"));
            args.append(app->config.getMountRoot());
            if(process.oneShot(tr("/usr/bin/mount"),args)) {
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
            args.append(tr("/dev/mapper/ControlPanel"));
            process.setArguments(args);
            if(!process.oneShot(tr("/usr/bin/umount"), args)) {
                setState(SYSTEM_ERROR, process.getLastError());
                break;
            }
            /* close device */
            args.clear();
            args.append(tr("close"));
            args.append(tr("/dev/mapper/ControlPanel"));
            process.setArguments(args);
            if(!process.oneShot(tr("/usr/sbin/cryptsetup"), args)) {
                setState(SYSTEM_ERROR, process.getLastError());
                break;
            }

            setStateOK();
        }while(0);
        process.clean();
    }
}
