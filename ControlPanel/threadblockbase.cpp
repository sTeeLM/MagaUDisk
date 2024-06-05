#include "threadblockbase.h"

ThreadBlockBase::ThreadBlockBase(QObject *parent, bool isMount)
    : StateThreadMount(parent, isMount)
    , blockinfo({})
{

}

void ThreadBlockBase::setBlockInfo(const QString & str)
{
    blockinfo = str.split(QChar('\n'), Qt::SkipEmptyParts);
}
