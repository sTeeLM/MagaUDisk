#include "mainwindow.h"

#include "controlpanelapplication.h"
#include "processcommander.h"
#include "pidfile.h"

#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    ControlPanelApplication a(argc, argv);

    /* write pid and lock */
    PidFile pidfile(&a, a.config.getPidFilePath());
    if(!pidfile.lock()) {
        exit(1);
    }

    QFont serifFont("苹方-简", 8, QFont::Normal);
    a.setFont(serifFont);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ControlPanel_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    ProcessCommander process;
    QStringList args;
    /* close vtcon */
    args.clear();
    args.append("-c");
    args.append("echo 0 > /sys/class/vtconsole/vtcon1/bind");
    process.oneShot("/usr/bin/sh", args);
    process.clean();

    MainWindow w;
    w.show();
    return a.exec();
}
