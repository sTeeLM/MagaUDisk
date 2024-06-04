#include "mainwindow.h"

#include "controlpanelapplication.h"

#include <QLocale>
#include <QTranslator>


int main(int argc, char *argv[])
{
    ControlPanelApplication a(argc, argv);

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
    MainWindow w;
    w.show();
    return a.exec();
}
