#include "threadchangepassword.h"

ThreadChangePassword::ThreadChangePassword(QObject *parent, const QString & oldPass, const QString & newPass, const QString & newPassAgain)
    : StateThreadBase{parent}
    , strOldPass(oldPass)
    , strNewPass(newPass)
    , strNewPassAgain(newPassAgain)
{

}

void ThreadChangePassword::run()
{
    QThread::sleep(1);
    setStateOK();
}
