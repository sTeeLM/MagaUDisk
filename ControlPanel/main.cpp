#include "mainwindow.h"

#include "controlpanelapplication.h"

#include <QLocale>
#include <QTranslator>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    ControlPanelApplication a(argc, argv);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption opt("f","config file","config");
    parser.addOption(opt);

    QStringList args;

    for(int i = 0 ; i < argc; i ++) {
        args.append(argv[i]);
    }

    parser.process(args);

    QString configFilePath = QObject::tr("/etc/ControlPanel.cfg");

    if(parser.isSet(opt)) {
        configFilePath =  parser.value(opt);
    }

    a.config.loadConfig(configFilePath);

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
