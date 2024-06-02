#include "processcommander.h"
#include <QProcess>
#include <QDebug>
#include <QRegExp>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <sys/time.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#ifndef __NR_pidfd_open
#define __NR_pidfd_open  434
#endif

#ifndef __NR_pidfd_send_signal
#define __NR_pidfd_send_signal  424
#endif

ProcessCommander::ProcessCommander(QObject *parent)
    : QObject(parent)
    , programName("")
    , fdStdin(-1)
    , fdStdout(-1)
    , fdStderr(-1)
    , childPid(-1)
    , fdPid(-1)
    , stdinBuffer("")
    , exitStatusSignal(0)    
    , processStatus(PROCESS_STATUS_EXIT)
    , lastError("")
{

}

static int pidfd_open(pid_t pid, unsigned int flags)
{
    return ::syscall(__NR_pidfd_open, pid, flags);
}

static int pidfd_send_signal(int pidfd, int sig, siginfo_t * info, unsigned int flags)
{
    return ::syscall(__NR_pidfd_send_signal, pidfd, sig, info, flags);
}

char ** ProcessCommander::QStringList2CharPP(const QStringList & list)
{
    char ** ret = nullptr;
    size_t length = list.length();

    ret = static_cast<char **>(::malloc((length + 1) * sizeof(char *)));
    if(ret != nullptr) {
        size_t i;
        for(i = 0 ; i < length; i ++) {
            size_t size = list.at(i).toLocal8Bit().length();
            ret[i] = static_cast<char *>(::malloc(size + 1));
            if(ret[i]) {
                ::strncpy(ret[i], list.at(i).toLocal8Bit().constData(), size);
                ret[i][size] = 0;
            } else {
                break;
            }
        }
        ret[i] = nullptr;
    }
    return ret;
}

void ProcessCommander::FreeCharPP(char ** p)
{
    int index = 0;
    if(p!= nullptr) {
        while(p[index] != nullptr) {
            ::free(p[index]);
            p[index] = nullptr;
            index ++;
        }
        ::free(p);
    }
}

bool ProcessCommander::ReadAppend(int fd, QByteArray & strList)
{
    char buffer[128];
    ssize_t ret = -1;
    bool retVal = false;
    do {
        ret = ::read(fd, buffer, sizeof(buffer) - 1);
        if(ret > 0) {
            buffer[ret] = 0;
            strList.append(buffer, ret);
            retVal = true;
        }
    }while(ret > 0);
    return retVal;
}

bool ProcessCommander::Match(QByteArray & strList, const QString & str)
{
    bool retVal = false;
    QString strBuffer = QString::fromLocal8Bit(strList);
    retVal =  strBuffer.indexOf(QRegExp(str)) != -1;
    return retVal;
}

void ProcessCommander::WriteAppend(int fd, QByteArray & toWrite, QByteArray & strList)
{
    ssize_t ret;
    int length = toWrite.length();
    if(length) {
        ret = ::write(fd, toWrite.constData(), toWrite.length());
        if(ret > 0) {
            strList.append(toWrite.left(ret));
            toWrite = toWrite.right(length - ret);
        }
    }
}

void ProcessCommander::updateLastError()
{
    char buffer[1024];
    ::strerror_r(errno, buffer, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = 0;
    lastError.fromLocal8Bit(buffer);
}

bool ProcessCommander::start()
{
    int pipeStdin[2] = {-1, -1};
    int pipeStdout[2] = {-1, -1};
    int pipeStderr[2] = {-1, -1};
    char ** args = nullptr;
    char ** envs = nullptr;
    bool retVal = false;

    /* argv[0] is program name ! */
    programArgs.prepend(programName);

    /* prepare buffers */
    if((args = QStringList2CharPP(programArgs)) == nullptr) {
        goto err;
    }

    if((envs = QStringList2CharPP(programEnvs)) == nullptr) {
        goto err;
    }

    /* create 3 pipe pair */
    if(::pipe(pipeStdin) != 0) {
        goto err;
    }

    if(fcntl(pipeStdin[1], F_SETFL, O_NONBLOCK | fcntl(pipeStdin[1], F_GETFL, 0)) < 0) {
        goto err;
    }

    if(::pipe(pipeStdout) != 0) {
        goto err;
    }

    if(fcntl(pipeStdout[0], F_SETFL, O_NONBLOCK | fcntl(pipeStdout[0], F_GETFL, 0)) < 0) {
        goto err;
    }

    if(::pipe(pipeStderr) != 0) {
        goto err;
    }

    if(fcntl(pipeStderr[0], F_SETFL, O_NONBLOCK | fcntl(pipeStderr[0], F_GETFL, 0)) < 0) {
        goto err;
    }

    if(::signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        goto err;
    }

    if((childPid = ::fork()) == -1) {
        goto err;
    }

    if(childPid == 0) { /* child */
        /* close unwanted pipe end */
        ::close(pipeStdin[1]);
        ::close(pipeStdout[0]);
        ::close(pipeStderr[0]);
        ::close(0);
        ::close(1);
        ::close(2);
        /* dup fds*/
        if(::dup2(pipeStdin[0], 0) < 0) {
            ::exit(1);
        }
        ::close(pipeStdin[0]);

        if(::dup2(pipeStdout[1], 1) < 0) {
            ::exit(1);
        }
        ::close(pipeStdout[1]);

        if(::dup2(pipeStderr[1], 2) < 0) {
            ::exit(1);
        }
        ::close(pipeStderr[1]);

        ::execve(programName.toLocal8Bit().constData(), args, envs);
        ::exit(1); /* should nevel go here */

    } else { /* parent */
        if((fdPid = pidfd_open(childPid, 0)) < 0) {
            ::kill(childPid, SIGTERM);
            goto err;
        }
        /* close unwanted pipe end */
        ::close(pipeStdin[0]);
        ::close(pipeStdout[1]);
        ::close(pipeStderr[1]);
        pipeStdin[0] = pipeStdout[1] = pipeStderr[1] = -1;
        fdStdin = pipeStdin[1];
        fdStdout = pipeStdout[0];
        fdStderr = pipeStderr[0];
        processStatus = PROCESS_STATUS_RUNNING;
        retVal = true;
    }
err:
    if(!retVal) {
        updateLastError();
        if(pipeStdin[0] >= 0)
            ::close(pipeStdin[0]);
        if(pipeStdin[1] >= 0)
            ::close(pipeStdin[1]);
        if(pipeStdout[0] >= 0)
            ::close(pipeStdout[0]);
        if(pipeStdout[1] >= 0)
            ::close(pipeStdout[1]);
        if(pipeStderr[0] >= 0)
            ::close(pipeStderr[0]);
        if(pipeStderr[1] >= 0)
            ::close(pipeStderr[1]);
    }
    FreeCharPP(args);
    FreeCharPP(envs);
    return retVal;
}

void ProcessCommander::clean()
{
    int status;
    if(processStatus == PROCESS_STATUS_STOP
            || processStatus == PROCESS_STATUS_RUNNING) {
        ::kill(childPid, SIGTERM);
        ::waitpid(childPid, &status, 0);
        childPid = -1;
    }
    if(fdStdin >= 0) {
        ::close(fdStdin);
        fdStdin = -1;
    }
    if(fdStdout >= 0) {
        ::close(fdStdout);
        fdStdin = -1;
    }
    if(fdStderr >= 0) {
        ::close(fdStderr);
        fdStderr = -1;
    }
    if(fdPid >= 0) {
        ::close(fdPid);
        fdPid = -1;
    }
}

void ProcessCommander::sendSignal(int signo)
{
    if(processStatus == PROCESS_STATUS_STOP
            || processStatus == PROCESS_STATUS_RUNNING) {
        ::kill(childPid, signo);
    }
}

#define _max(a, b) \
    ((a) > (b) ? (a) : (b))


void ProcessCommander::UpdateWaitStatus()
{
    pid_t wait;
    int status;

    wait = ::waitpid(childPid, &status, WNOHANG);
    if(wait == childPid) {
        if(WIFEXITED(status)) { /* exit */
                exitStatusSignal = WEXITSTATUS(status);
                processStatus = PROCESS_STATUS_EXIT;
        } else if(WIFSIGNALED(status)) {
                exitStatusSignal = WTERMSIG(status);
                processStatus = PROCESS_STATUS_SIGNAL;
        } else if(WIFSTOPPED(status)) {
                processStatus = PROCESS_STATUS_STOP;
            } else if(WIFCONTINUED(status)) {
                processStatus = PROCESS_STATUS_RUNNING;
        }
    }
}

bool ProcessCommander::checkTimeout(
        const struct timeval & begin,
        const struct timeval & end,
        int & timeoutMS)
{
    int diffMs;
    if(timeoutMS <= 0) return false;

    /* end - begin in ms */
    /* end.tv_sec * 1000 + end.tv_usec / 1000 - begin.tv_sec * 1000 - begin.tv_usec / 1000 */
    diffMs = (end.tv_sec - begin.tv_sec) * 1000 +
            (end.tv_usec - begin.tv_usec) / 1000;

    if(diffMs >= 0) {
        if(timeoutMS > diffMs) {
            timeoutMS -= diffMs;
            return false;
        }
    } else {
       /* should not be here ..., clock sync ? */
       return false;
    }
    return true;
}

int
ProcessCommander::waitForConditions(
        const QString & stdOut,
        const QString & stdErr,
        int waitMask,
        int timeoutMS)
{
    fd_set readfds, writefds;
    struct timeval timeout, timebegin, timeend;
    int ready, nfds = -1, ret = WAIT_MASK_ERROR;

    while(1) {
        FD_ZERO(&readfds); FD_ZERO(&writefds);
        memset(&timeout, 0, sizeof(timeout));

        /* 10ms */
        timeout.tv_sec = 0;
        timeout.tv_usec = 10000;

        if(stdinBuffer.length()) {
            FD_SET(fdStdin, &writefds);
            nfds = _max(nfds, fdStdin);
        }
        if(waitMask & WAIT_MASK_STATUS) {
            FD_SET(fdPid, &readfds);
            nfds = _max(nfds, fdPid);
        }
        if(waitMask & WAIT_MASK_STDOUT) {
            FD_SET(fdStdout, &readfds);
            nfds = _max(nfds, fdStdout);
        }
        if(waitMask & WAIT_MASK_STDERR) {
            FD_SET(fdStderr, &readfds);
            nfds = _max(nfds, fdStderr);
        }
        nfds ++;
        ret = WAIT_MASK_NONE;
        ::gettimeofday(&timebegin, NULL);
        ready = ::select(nfds, &readfds, &writefds, NULL, timeoutMS > 0 ? &timeout : NULL);
        ::gettimeofday(&timeend, NULL);
        if(ready > 0) { /* check fds */
            if(FD_ISSET(fdStdin, &writefds)) {
                WriteAppend(fdStdin, stdinBuffer, programStdin);
            }
            if(FD_ISSET(fdStdout, &readfds)) {
                if(ReadAppend(fdStdout, programStdout) && (waitMask & WAIT_MASK_STDOUT)) {
                    if(Match(programStdout, stdOut)) {
                        ret |= WAIT_MASK_STDOUT;
                    }
                }
            }
            if(FD_ISSET(fdStderr, &readfds)) {
                if(ReadAppend(fdStderr, programStderr) && (waitMask & WAIT_MASK_STDERR)) {
                    if(Match(programStderr, stdErr)) {
                        ret |= WAIT_MASK_STDERR;
                    }
                }
            }
            if((waitMask & WAIT_MASK_STATUS) && FD_ISSET(fdPid, &readfds)) {
                ret |= WAIT_MASK_STATUS;
            }
            UpdateWaitStatus();
            if(ret != WAIT_MASK_NONE) {
                break;
            }
        } else if(ready == 0) { /* timeout */
            if(checkTimeout(timebegin, timeend, timeoutMS)) {
                ret = WAIT_MASK_NONE;
                break;
            }
        } else { /* error ? */
            ret = WAIT_MASK_ERROR;
            updateLastError();
            break;
        }
    }

    return ret;
}



