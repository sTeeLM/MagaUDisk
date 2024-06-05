#ifndef THREADMOUNTIMAGE_H
#define THREADMOUNTIMAGE_H

#include <QObject>
#include "threadblockbase.h"

class ThreadMountImage : public ThreadBlockBase
{
    Q_OBJECT
public:
    explicit ThreadMountImage(QObject *parent = nullptr, bool isMount = true, const QString & image = {});
    void run();
private:
    QString imagePath;
};

#endif // THREADMOUNTIMAGE_H
