#include "killerthread.h"

KillerThread* KillerThread::instance = 0;

KillerThread::KillerThread()
{
}

KillerThread& KillerThread::Instance()
{
    if(!instance)
        instance = new KillerThread();
    return *instance;
}

void KillerThread::Kill()
{
    emit exit();
}


