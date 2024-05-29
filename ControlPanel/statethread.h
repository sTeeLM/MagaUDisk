#ifndef STATETHREAD_H
#define STATETHREAD_H

#include <QObject>
#include <QThread>

class StateThread : public QThread
{
    Q_OBJECT
public:
    explicit StateThread(QObject *parent = nullptr);
public:
    enum FINISH_STATE {
      OK = 0,
      FAILED
    };

public:
    void setOK()
    {
        state = OK;
    }
    void setFailed(QString & str)
    {
        strState = str;
        state = FAILED;
    }
private:
    QString strState;
    FINISH_STATE state;
};

#endif // STATETHREAD_H
