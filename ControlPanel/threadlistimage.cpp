#include "threadlistimage.h"
#include "controlpanelapplication.h"
#include "processcommander.h"

#include <QDebug>
#include <QFile>
#include <QApplication>
#include <QStringList>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>

ThreadListImage::ThreadListImage(QObject *parent, QListWidget * list, const QString & path)
    : StateThreadBase(parent)
    , listImage(list)
    , listPath(path)
{

}

void ThreadListImage::run()
{

    ControlPanelApplication * app = qobject_cast<ControlPanelApplication *>(qApp);
    int count = listImage->count();
    /* clear all item */
    for(int i = 0 ; i < count; i ++) {
        delete listImage->item(i);
    }
    listImage->clear();

    QString path = app->config.getMountRoot();
    if(path.right(1) == QString("/")) {
        path.chop(1);
    }
    path += listPath;
    qDebug() << tr("ThreadListImage::run list path is %1").arg(path);

    QDir dir(path);
    dir.setSorting(QDir::Name);
    QFileInfoList list = dir.entryInfoList();

    for(int i = 0 ; i < list.size(); i ++) {
        QFileInfo fileInfo = list.at(i);
        int type = list.at(i).isDir() ? 0 : 1;
        QString name = list.at(i).fileName();
        if(name != QString(".")) {
            QString iconPath = app->config.getIconFolder();
            if(iconPath.right(1) != QChar('/')) {
                iconPath += QString("/");
            }
            if(type == 0) {
                iconPath += QString("folder.png");
            } else {
                if(name.lastIndexOf(".iso", -1, Qt::CaseInsensitive) >= 0) {
                    iconPath += QString("cdrom.png");
                } else if(name.lastIndexOf(".img", -1, Qt::CaseInsensitive) >= 0) {
                    iconPath += QString("hdd.png");
                } else {
                    iconPath += QString("default.png");
                }
            }
            QListWidgetItem * item
                    = new QListWidgetItem(QIcon(iconPath), name , listImage, type);
            listImage->addItem(item);
        }
    }
    setStateOK();
}
