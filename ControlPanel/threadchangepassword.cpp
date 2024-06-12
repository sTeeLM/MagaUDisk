#include "threadchangepassword.h"
#include "controlpanelapplication.h"
#include "processcommander.h"

#include <QDebug>
ThreadChangePassword::ThreadChangePassword(QObject *parent, const QString & oldPass, const QString & newPass, const QString & newPassAgain)
    : StateThreadBase{parent}
    , strOldPass(oldPass)
    , strNewPass(newPass)
    , strNewPassAgain(newPassAgain)
{

}

void ThreadChangePassword::run()
{
    ProcessCommander process;
    QStringList args;
    QString stdin;
    ControlPanelApplication * app = qobject_cast<ControlPanelApplication *>(qApp);
    int excode;

    do {
        if(strOldPass.length() == 0 || strNewPass.length() == 0 || strNewPassAgain.length() == 0) {
            setState(CHANGE_PASS_FAILED, "密码为空!");
            break;
        }
        if(strNewPass != strNewPassAgain) {
            setState(CHANGE_PASS_FAILED, "两次新密码不匹配!");
            break;
        }
        if(strNewPass == strOldPass) {
            setState(CHANGE_PASS_FAILED, "新旧密码相同!");
            break;
        }

        /* change password */
        args.clear();
        args.append("luksChangeKey");
        args.append(app->config.getSourcePartation());
        process.setArguments(args);
        stdin = strOldPass + QString("\n") + strNewPass + QString("\n") + strNewPassAgain + QString("\n");
        if(!process.oneShot("/usr/sbin/cryptsetup",
                            args,
                            {},
                            stdin,
                            &excode,
                            app->config.getCommandTimeoutMs()) || excode != 0) {
            setState(CHANGE_PASS_FAILED, process.getLastError());
            break;
        }

        setStateOK();
    }while(0);
    process.clean();
}
