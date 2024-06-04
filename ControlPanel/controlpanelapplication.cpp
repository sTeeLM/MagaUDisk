#include "controlpanelapplication.h"
#include <QCommandLineParser>
ControlPanelApplication::ControlPanelApplication(int & argc, char ** argv)
    :QApplication(argc, argv),
    config(this)
{

    QCommandLineParser parser;
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

    config.loadConfig(configFilePath);
}


