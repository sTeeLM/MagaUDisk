#ifndef THREADBLOCKBASE_H
#define THREADBLOCKBASE_H

#include "statethreadmount.h"
#include <QObject>

class ThreadBlockBase : public StateThreadMount
{
    Q_OBJECT
public:
    explicit ThreadBlockBase(QObject *parent = nullptr, bool isMount = false);
    void setBlockInfo(const QString & str);

    const QStringList & getBlockInfo()
    {
        return blockinfo;
    }
private:
    QStringList blockinfo;
};

#endif // THREADBLOCKBASE_H
