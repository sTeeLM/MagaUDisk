#include "threadlistnic.h"
#include "processcommander.h"
#include "nicitem.h"

#include <QtDebug>
#include <QRegularExpression>

ThreadListNic::ThreadListNic(QObject *parent, QTreeWidget * tree)
    : StateThreadBase(parent)
    , treeNic(tree)
{

}

void ThreadListNic::run()
{
    ProcessCommander process;
    QStringList args, envs;
    QString stdout;

    qDebug() << tr("ThreadListNic::run");

    /* clear all item */
    QTreeWidgetItemIterator it(treeNic);
    while (*it) {
        delete (*it);
    }
    treeNic->clear();


    do {
        /* list bssid/ssid/signal/security */
        args.clear();
        args.append("-c");
        args.append("no");
        args.append("-f");
        args.append("bssid,ssid,signal,security");
        args.append("-e");
        args.append("no");
        args.append("--terse");
        args.append("device");
        args.append("wifi");
        args.append("list");
        envs.append("PATH=/bin:/usr/bin:/sbin/usr/sbin");
        envs.append("LANG=zh_CN.UTF-8");
        if(!process.oneShot(tr("/usr/bin/nmcli"), args, envs)) {
            setState(SYSTEM_ERROR, QString::fromLocal8Bit(process.getStderr()));
            break;
        }
        stdout = QString::fromLocal8Bit(process.getStdout());

        /* match values */
        QRegularExpression re("([A-Z0-9]{2}:[A-Z0-9]{2}:[A-Z0-9]{2}:[A-Z0-9]{2}:[A-Z0-9]{2}:[A-Z0-9]{2}):(.*):(.*):(.*)\\n");
        QRegularExpressionMatchIterator i = re.globalMatch(stdout);
        while (i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            qDebug() << tr("find '%1' '%2' '%3' '%4'").arg(match.captured(1),
                                                           match.captured(2),
                                                           match.captured(3),
                                                           match.captured(4));
            if(match.captured(2).size()) { /* ssid not null */
                NicItem * item = new NicItem(treeNic,
                                             match.captured(1),
                                             match.captured(2),
                                             match.captured(3),
                                             match.captured(4));
                treeNic->insertTopLevelItem(0, item);
            }

        }
        setStateOK();
    }while(0);
    process.clean();
}
