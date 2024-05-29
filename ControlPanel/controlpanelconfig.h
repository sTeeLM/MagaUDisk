#ifndef CONTROLPANELCONFIG_H
#define CONTROLPANELCONFIG_H

#include <QObject>

class ControlPanelConfig : public QObject
{
    Q_OBJECT
public:
    explicit ControlPanelConfig(QObject *parent = nullptr);

public:
    bool loadConfig();

private:


signals:
};

#endif // CONTROLPANELCONFIG_H
