#ifndef NICITEM_H
#define NICITEM_H

#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QObject>
#include <QWidget>

class NicItem : public QTreeWidgetItem
{
//    Q_OBJECT
public:
    explicit NicItem(QTreeWidget *parent = nullptr, const QString & bssid = {}, const QString & ssid = {}, const QString & signal = {}, const QString & security = {});
    const QString & getBssid()
    {
        return bssid;
    }
    void setBssid(const QString & v) {
        bssid = v;
    }
    const QString & getSsid()
    {
        return ssid;
    }
    void setSsid(const QString & v) {
        ssid = v;
    }
    const QString & getSecurity()
    {
        return security;
    }
    void setSecurity(const QString & v) {
        security = v;
    }
    const QString & getSignal()
    {
        return signal;
    }
    void setSignal(const QString & v) {
        signal = v;
    }
private:
    QString bssid;
    QString ssid;
    QString signal;
    QString security;
};

#endif // NICITEM_H
