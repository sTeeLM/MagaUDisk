#include "controlpanelapplication.h"
#include "threadpreparedevice.h"

#include <QApplication>
#include <QProcess>
#include <QStringList>

ThreadPrepareDevice::ThreadPrepareDevice(QObject *parent, const QString & password)
    :StateThreadBase(parent)
    ,strPassword(password)
{

}

void ThreadPrepareDevice::run()
{
    QProcess process(this);
    QStringList args;
    QString cmd = tr("cryptsetup");
    ControlPanelApplication * app = qobject_cast<ControlPanelApplication *>(qApp);

    args.append("luksOpen");
    args.append(app->config.getSourcePartation());
    args.append("ControlPanel");

    process.start(cmd, args);
    process.write(strPassword.toLocal8Bit());

    while(!process.waitForFinished(1000)) {
        QByteArray stdout = process.readAllStandardOutput();
        QString strStdout = QString::fromLocal8Bit(stdout);
        qDebug() << tr("stdout: %1").arg(strStdout);
        if(strStdout == QString(tr("No key available with this passphrase."))) {

        }
    }

}
