#include "controlpanelconfig.h"

#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

ControlPanelConfig::ControlPanelConfig(QObject *parent)
    : QObject(parent)
    , sourcePartation("/dev/mmcblk0p3")
    , iconFolder("/usr/share/ControlPanel/icons")
    , mountRoot("/mnt")
    , commandTimeoutMs(30000)
    , idVendor("0x781")
    , idProduct("0x5572")
    , bcdDevice("0x011a")
    , iManufacturer("Madcat")
    , iProduct("Mega UDisk")
    , iSerialNumber("198004091200")
{

}
/*
  "id_vendor" : "0x781"
  "id_product" : "0x5572",
  "bcd_device" : "0x011a",
  "i_manufacturer" : "Madcat",
  "i_product" : "Mega UDisk",
  "i_serial_number" : "198004091200",
  "nic_ip" : "10.10.0.1",
  "nic_mask" : "255.255.0.0"
*/
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
            if(jsonConfig.value("source_partation").isString()) {
                sourcePartation = jsonConfig.value("source_partation").toString();
            }
            if(jsonConfig.value("icon_folder").isString()) {
                iconFolder = jsonConfig.value("icon_folder").toString();
            }
            if(jsonConfig.value("mount_root").isString()) {
                mountRoot = jsonConfig.value("mount_root").toString();
            }
            if(jsonConfig.value("command_timeout_ms").isDouble()) {
                commandTimeoutMs = jsonConfig.value("command_timeout_ms").toInt();
            }
            if(jsonConfig.value("id_vendor").isString()) {
                idVendor = jsonConfig.value("id_vendor").toString();;
            }
            if(jsonConfig.value("id_product").isString()) {
                idProduct = jsonConfig.value("id_product").toString();
            }
            if(jsonConfig.value("bcd_device").isString()) {
                bcdDevice = jsonConfig.value("bcd_device").toString();
            }
            if(jsonConfig.value("i_manufacturer").isString()) {
                iManufacturer = jsonConfig.value("i_manufacturer").toString();
            }
            if(jsonConfig.value("i_product").isString()) {
                iProduct = jsonConfig.value("i_product").toString();
            }
            if(jsonConfig.value("i_serial_number").isString()) {
                iSerialNumber = jsonConfig.value("i_serial_number").toString();
            }
        } else {
            qDebug() << tr("config file %s open error!").arg(config);
        }
    } else {
        qDebug() << tr("config file %s open error!").arg(config);
    }

    qDebug() << tr("source_partation: %1").arg(sourcePartation);
    qDebug() << tr("icon_folder: %1").arg(iconFolder);
    qDebug() << tr("mount_root: %1").arg(mountRoot);
    qDebug() << tr("command_timeout_ms: %1").arg(commandTimeoutMs);
    qDebug() << tr("id_vendor: %1").arg(idVendor);
    qDebug() << tr("id_product: %1").arg(idProduct);
    qDebug() << tr("bcd_device: %1").arg(bcdDevice);
    qDebug() << tr("i_manufacturer: %1").arg(iManufacturer);
    qDebug() << tr("i_product: %1").arg(iProduct);
    qDebug() << tr("i_serial_number: %1").arg(iSerialNumber);
}

