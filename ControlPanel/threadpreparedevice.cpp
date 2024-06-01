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

    args.append(tr("-la"));
    env.append(tr("PATH=/usr/bin:/usr/sbin"));
    process.setProgram(tr("ls"));
    process.setArguments(args);
    process.setEnvironment(env);

    process.start();

    QString stdout = tr("总计");
    int ret = process.waitForConditions(stdout, {}, WAIT_MASK_STATUS|WAIT_MASK_STDOUT);

    process.clean();
}
