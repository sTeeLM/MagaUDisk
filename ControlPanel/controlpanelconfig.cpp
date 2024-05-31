#include "controlpanelconfig.h"

#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

ControlPanelConfig::ControlPanelConfig(QObject *parent)
    : QObject(parent)
    , sourcePartation(tr("/dev/mmcblk0p3"))
    , iconFolder(tr("/usr/share/ControlPanel/icons"))
    , mountRoot(tr("/mnt"))
{

}

void ControlPanelConfig::loadConfig(const QString & config)
{
    qDebug() << QObject::tr("use config file %1").arg(config);
    QFile fileConfig(config);

    if(fileConfig.open(QFile::ReadOnly)) {

        QByteArray dataConfig = fileConfig.readAll();
        QJsonDocument jsonDocConfig = QJsonDocument::fromJson(dataConfig);
        fileConfig.close();

        if(jsonDocConfig.isObject()) {
            QJsonObject jsonConfig = jsonDocConfig.object();
            if(jsonConfig.value(tr("source_partation")).isString()) {
                sourcePartation = jsonConfig.value(tr("source_partation")).toString();
            }
            if(jsonConfig.value(tr("icon_folder")).isString()) {
                iconFolder = jsonConfig.value(tr("icon_folder")).toString();
            }
            if(jsonConfig.value(tr("mount_root")).isString()) {
                mountRoot = jsonConfig.value(tr("mount_root")).toString();
            }
        }
    } else {
        qDebug() << tr("config file %s open error!").arg(config);
    }

    qDebug() << tr("source_partation: %1").arg(sourcePartation);
    qDebug() << tr("icon_folder: %1").arg(iconFolder);
    qDebug() << tr("mount_root: %1").arg(mountRoot);
}

