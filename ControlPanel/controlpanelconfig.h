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
    void loadConfig(const QString & config);

    const QString & getSourcePartation()
    {
        return sourcePartation;
    }

    const QString & getIconFolder()
    {
        return iconFolder;
    }

    const QString & getMountRoot()
    {
        return mountRoot;
    }

    int getCommandTimeoutMs()
    {
        return commandTimeoutMs;
    }

private:

    QString sourcePartation;
    QString iconFolder;
    QString mountRoot;
    int     commandTimeoutMs;
signals:
};

#endif // CONTROLPANELCONFIG_H
