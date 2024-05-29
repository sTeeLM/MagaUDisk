#ifndef CONTROLPANELCONFIG_H
#define CONTROLPANELCONFIG_H

#include <QObject>

class ControlPanelConfig : public QObject
{
    Q_OBJECT
public:
    explicit ControlPanelConfig(QObject *parent = nullptr);

public:
    // 装载配置和保存状态
    void loadConfigAndState();

    bool isEncryptPart();

private:


signals:
};

#endif // CONTROLPANELCONFIG_H
