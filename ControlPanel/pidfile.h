#ifndef PIDFILE_H
#define PIDFILE_H

#include <QObject>
#include <QCoreApplication>

class PidFile : public QObject
{
    Q_OBJECT
public:
    explicit PidFile(QCoreApplication *parent = nullptr, const QString & filepath = {});
    bool lock();

private:
    QCoreApplication * app;
    QString pidFile;
signals:

};

#endif // PIDFILE_H
