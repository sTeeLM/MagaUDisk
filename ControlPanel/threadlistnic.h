#ifndef THREADLISTNIC_H
#define THREADLISTNIC_H

#include "statethreadbase.h"
#include <QObject>
#include <QTreeWidget>

class ThreadListNic : public StateThreadBase
{
    Q_OBJECT
public:
    explicit ThreadListNic(QObject *parent = nullptr, QTreeWidget * tree = nullptr);
    void run();

private:
    QTreeWidget  * treeNic;
};

#endif // THREADLISTNIC_H
