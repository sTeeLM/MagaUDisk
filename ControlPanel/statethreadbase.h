#ifndef STATETHREADBASE_H
#define STATETHREADBASE_H

#include <QObject>
#include <QThread>

class StateThreadBase : public QThread
{
    Q_OBJECT
public:
    explicit StateThreadBase(QObject *parent = nullptr);
public:
    enum FINISH_STATE {
      OK = 0,
      WRONG_PASS,
      MISMATCH_PASS,
      CHANGE_PASS_FAILED,
      MOUNT_PART_FAILED,
      UNMOUNT_PART_FAILED,
      MOUNT_IMAGE_FAILED,
      UNMOUNT_IMAGE_FAILED,
      MOUNT_SERIAL_FAILED,
      UNMOUNT_SERIAL_FAILED,
      MOUNT_NIC_FAILED,
      UNMOUNT_NIC_FAILED,
      SYSTEM_ERROR,
      UNKNOWN_FAILED
    };

public:
    void setStateOK()
    {
        state = OK;
        translateState();
    }
    void setState(FINISH_STATE s, const QString & extra = {})
    {
        strStateExtra = extra;
        state = s;
        translateState();
    }
    bool isStateOK()
    {
        return state == OK;
    }
    QString & getStateString()
    {
        return strState;
    }
    QString & getExtra()
    {
        return strStateExtra;
    }
    FINISH_STATE getState()
    {
        return state;
    }   

private:
    void translateState();
    QString strState;
    QString strStateExtra;
    FINISH_STATE state;
};

#endif // STATETHREADBASE_H
