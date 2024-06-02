#ifndef PROCESSCOMMANDER_H
#define PROCESSCOMMANDER_H

#include <QObject>


class ProcessCommander : public QObject
{
    Q_OBJECT
public:
    explicit ProcessCommander(QObject *parent = nullptr);

/* shit happens */
#define WAIT_MASK_ERROR          0xFF
/* time out */
#define WAIT_MASK_NONE           0x0
/* process status changed: exit, killed, stopped */
#define WAIT_MASK_STATUS         0x1
/* stdout matchs */
#define WAIT_MASK_STDOUT         0x2
/* stderr matchs */
#define WAIT_MASK_STDERR         0x4
/*
    enum WAIT_MASK {
        WAIT_MASK_ERROR  = 0,
        WAIT_MASK_STATUS = 1,
        WAIT_MASK_STDOUT = 2,
        WAIT_MASK_STATUS_STDOUT = 3,
        WAIT_MASK_STDERR  = 4,
        WAIT_MASK_STATUS_STDERR = 5,
        WAIT_MASK_STDOUT_STDERR = 6,
        WAIT_MASK_ALL = 7
    };
*/
    void setProgram(const QString & program)
    {
        programName = program;
    }
    const QString & getProgram()
    {
        return programName;
    }

    void setArguments(const QStringList & args)
    {
        programArgs = args;
    }
    const QStringList & getArguments()
    {
        return programArgs;
    }

    void setEnvironment(const QStringList & envs)
    {
        programEnvs = envs;
    }
    const QStringList & getEnvironment()
    {
        return programEnvs;
    }
    bool start();
    void clean();
    void sendSignal(int signo);
    void writeStdin(const QByteArray & stdin)
    {
        stdinBuffer.append(stdin);
    }

    int  waitForConditions(const QString & stdOut = {}, const QString & stdErr = {},
                                int waitMask = WAIT_MASK_STATUS, int timeoutMS = 0);
    enum PROCESS_STATUS {
        PROCESS_STATUS_EXIT,
        PROCESS_STATUS_SIGNAL,
        PROCESS_STATUS_STOP,
        PROCESS_STATUS_RUNNING
    };

    bool isRunning()
    {
        return processStatus == PROCESS_STATUS_RUNNING;
    }
    bool isExited(int * exitCode = nullptr)
    {
        if(exitCode)
            *exitCode = exitStatusSignal;
        return processStatus == PROCESS_STATUS_EXIT;
    }
    bool isSignaled(int * signalNo = nullptr)
    {
        if(signalNo)
            *signalNo = exitStatusSignal;
        return processStatus == PROCESS_STATUS_SIGNAL;
    }
    bool isStopped()
    {
        return processStatus == PROCESS_STATUS_STOP;
    }

    const QByteArray & getStdout()
    {
        return programStdin;
    }
    const QByteArray & getStderr()
    {
        return programStdout;
    }
    const QByteArray & getStdin()
    {
        return programStderr;
    }

    const QString & getLastError()
    {
        return lastError;
    }
private:
    QString programName;
    QStringList programArgs;
    QStringList programEnvs;
    QByteArray programStdin;
    QByteArray programStdout;
    QByteArray programStderr;
    int fdStdin;
    int fdStdout;
    int fdStderr;
    pid_t childPid;
    int fdPid;
    QByteArray stdinBuffer;
    int exitStatusSignal;
    PROCESS_STATUS processStatus;
    QString lastError;

    bool Match(QByteArray & strList, const QString & str);
    bool ReadAppend(int fd, QByteArray & strList);
    void WriteAppend(int fd, QByteArray & toWrite, QByteArray & strList);
    void UpdateWaitStatus();
    char ** QStringList2CharPP(const QStringList & list);
    void FreeCharPP(char ** p);
    bool checkTimeout(const struct timeval & begin, const struct timeval & end, int & timeoutMS);
    void updateLastError();
};

#endif // PROCESSCOMMANDER_H
