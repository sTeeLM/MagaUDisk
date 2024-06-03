#ifndef THREADMOUNTIMAGE_H
#define THREADMOUNTIMAGE_H

#include <QObject>
#include "statethreadmount.h"

class ThreadMountImage : public StateThreadMount
{
    Q_OBJECT
public:
    explicit ThreadMountImage(QObject *parent = nullptr, bool isMount = true, const QString & image = {});
private:
    QString imagePath;
};

#endif // THREADMOUNTIMAGE_H
