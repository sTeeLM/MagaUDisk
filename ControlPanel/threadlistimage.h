#ifndef THREADLISTIMAGE_H
#define THREADLISTIMAGE_H

#include <QObject>
#include <QListWidget>
#include "statethreadbase.h"

class ThreadListImage : public StateThreadBase
{
    Q_OBJECT
public:
    explicit ThreadListImage(QObject *parent = nullptr, QListWidget * list = nullptr, const QString & path = {});
    void run();
private:
    QListWidget * listImage;
    QString listPath;
};

#endif // THREADLISTIMAGE_H
