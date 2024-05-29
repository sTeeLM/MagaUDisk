#include "controlpanelconfig.h"

ControlPanelConfig::ControlPanelConfig(QObject *parent)
    : QObject{parent}
{

}

void ControlPanelConfig::loadConfigAndState()
{


}

bool ControlPanelConfig::isEncryptPart()
{
    return false;
}
