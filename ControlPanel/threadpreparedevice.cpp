#include "controlpanelapplication.h"
#include "threadpreparedevice.h"
#include "processcommander.h"

#include <QDebug>
#include <QApplication>
#include <QStringList>

ThreadPrepareDevice::ThreadPrepareDevice(QObject *parent, const QString & password)
    :StateThreadBase(parent)
    ,strPassword(password)
{

}

void ThreadPrepareDevice::run()
{
    ProcessCommander process;
    QStringList args, env;
    int retVal, exCode = -1;
    QString stderr;
    ControlPanelApplication * app = qobject_cast<ControlPanelApplication *>(qApp);

    process.setProgram(tr("/usr/sbin/cryptsetup"));
    args.append(tr("open"));
    args.append(app->config.getSourcePartation());
    args.append(tr("ControlPanel"));
    env.append(tr("PATH=/usr/bin:/usr/sbin"));
    process.setArguments(args);
    process.setEnvironment(env);

    do {
        if(!process.start()) {
            setState(SYSTEM_ERROR, process.getLastError());
            break;
        }

        process.writeStdin(strPassword.append("\n").toLocal8Bit());
        stderr = tr("No key available with this passphrase\\.\\n$");
        retVal = process.waitForConditions({}, stderr, WAIT_MASK_STDERR|WAIT_MASK_STATUS, 10000);

        if(retVal & WAIT_MASK_STDERR) {
            setState(WRONG_PASS, QString(process.getStderr()));
            break;
        }

        if((retVal & WAIT_MASK_STATUS) && process.isExited(&exCode) && exCode == 0) {
            setStateOK();
            break;
        } else {
            setState(SYSTEM_ERROR, QString(process.getStderr()));
            break;
        }
    }while(0);

    process.clean();
}
