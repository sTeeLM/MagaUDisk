#include "nicitem.h"

NicItem::NicItem(QTreeWidget *parent, const QString & bssid, const QString & ssid, const QString & signal, const QString & security)
    : QTreeWidgetItem(parent)
    , bssid(bssid)
    , ssid(ssid)
    , signal(signal)
    , security(security)
{
    setText(0, ssid);
    setText(1, signal);
    setText(2, security);
    setText(3, bssid);
}
