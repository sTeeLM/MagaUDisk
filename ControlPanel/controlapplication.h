#ifndef CONTROLAPPLICATION_H
#define CONTROLAPPLICATION_H

#include "controlpanelconfig.h"

#include <QApplication>
#include <QObject>

class ControlApplication : public QApplication
{
    Q_OBJECT
public:
    ControlApplication(int argc, char ** argv);
private:
    ControlPanelConfig config;
};

#endif // CONTROLAPPLICATION_H
