#ifndef CONTROLPANELAPPLICATION_H
#define CONTROLPANELAPPLICATION_H

#include "controlpanelconfig.h"

#include <QApplication>
#include <QObject>

class ControlPanelApplication : public QApplication
{
    Q_OBJECT
public:
    ControlPanelApplication(int argc, char ** argv);
    ControlPanelConfig config;
};

#endif // CONTROLPANELAPPLICATION_H
