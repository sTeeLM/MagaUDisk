#ifndef THREADCHANGEPASSWORD_H
#define THREADCHANGEPASSWORD_H

#include <QObject>
#include "statethreadbase.h"

class ThreadChangePassword : public StateThreadBase
{
    Q_OBJECT
public:
    explicit ThreadChangePassword(QObject *parent , const QString & oldPass, const QString & newPass, const QString & newPassAgain);
    void run();
private:
    QString strOldPass;
    QString strNewPass;
    QString strNewPassAgain;
};

#endif // THREADCHANGEPASSWORD_H
