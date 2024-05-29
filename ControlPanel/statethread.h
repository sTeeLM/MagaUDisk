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
      WRONG_PASS,
      FAILED
    };

public:
    void setOK()
    {
        state = OK;
    }
    void setFailed(FINISH_STATE s, const QString & str)
    {
        strState = str;
        state = s;
    }
    bool isOK()
    {
        return state == OK;
    }
    QString & getStateString()
    {
        return strState;
    }
    FINISH_STATE getState()
    {
        return state;
    }
private:
    QString strState;
    FINISH_STATE state;
};

#endif // STATETHREAD_H
