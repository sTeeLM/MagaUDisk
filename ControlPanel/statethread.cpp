#include "statethread.h"

StateThread::StateThread(QObject *parent)
    : QThread(parent)
    , strState(tr(""))
    , state(StateThread::OK)
{

}
