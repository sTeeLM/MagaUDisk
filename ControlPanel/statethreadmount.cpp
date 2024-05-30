#include "statethreadmount.h"

StateThreadMount::StateThreadMount(QObject *parent, bool isMount)
    : StateThreadBase{parent}
    , isMountThread(isMount)
{}
