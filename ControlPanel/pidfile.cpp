#include "pidfile.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <QDebug>
#include <QProcess>

PidFile::PidFile(QCoreApplication *parent, const QString & pid)
    : app(parent)
    , pidFile(pid)
{

}

bool PidFile::lock()
{
    int fd = -1;
    struct flock lock, savelock;
    bool retVal = false;
    QString pidstr;
    int length;

    do {

        if((fd = ::open(pidFile.toLocal8Bit().data(), O_RDWR|O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0) {
            qDebug() << tr("PidFile::lock can not open pid file %1 %2").arg(pidFile).arg(strerror(errno));
            break;
        }

        lock.l_type    = F_WRLCK;   /* Test for any lock on any part of file. */
        lock.l_start   = 0;
        lock.l_whence  = SEEK_SET;
        lock.l_len     = 0;
        savelock       = lock;

        if(::fcntl(fd, F_GETLK, &lock) < 0) {  /* Overwrites lock structure with preventors. */
            qDebug() << tr("PidFile::lock fcntl F_GETLK error %1").arg(strerror(errno));
            break;
        }

        if (lock.l_type == F_WRLCK || lock.l_type == F_RDLCK) {
            qDebug() << tr("PidFile::Process %1 has a write lock already!").arg(lock.l_pid);
            break;
        }

        if(::fcntl(fd, F_SETLK, &savelock) < 0) {
            qDebug() << tr("PidFile::lock fcntl F_SETLK error %1").arg(strerror(errno));
            break;
        }

        pidstr = QString::asprintf("%lld", app->applicationPid());
        length = pidstr.toLocal8Bit().length();
        if(::write(fd, pidstr.toLocal8Bit().data(), length) != length) {
            qDebug() << tr("PidFile::lock write error %1").arg(strerror(errno));
            break;
        }

        if(::fsync(fd) < 0) {
            qDebug() << tr("PidFile::lock fsync error %1").arg(strerror(errno));
            break;
        }

        retVal = true;
    }while(0);

    if(!retVal) {
        if(fd >= 0) {
            ::close(fd);
            fd = -1;
        }
    }

    return retVal;
}
