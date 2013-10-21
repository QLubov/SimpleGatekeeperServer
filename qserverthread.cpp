#include "qserverthread.h"

QServerThread::QServerThread(QObject *parent) :
    QThread(parent)
{
    needToClose = true;
}

void QServerThread::run()
{

    H323EndPoint ep;
    //server = new GatekeeperServer(ep);
    GatekeeperServer serv(ep);
    LogManager &log = LogManager::Instance();
    log.clearLogs();
    log.PushLog(QString("server run!"));
    ActionManager &mng = ActionManager::Instance();
    while(needToClose && mng.GetCountOfCommand())
    {
    }
    //delete server;
    if(mng.IsSuccessed())
        log.PushLog(QString("Scenario was successfully finished"));
    else
       log.PushLog(QString("server stop"));

    //return;
}
void QServerThread::StartThread(QFile *file)
{
    LogManager &log = LogManager::Instance();
    connect(&log, SIGNAL(updateLogs(QString)), this, SIGNAL(update(QString)));
    log.PushLog(QString("Scenario " + file->fileName() + " opened"));
    ActionManager &mng = ActionManager::Instance();
    mng.ParseXML(file);    
    this->start();
}
void QServerThread::end()
{    
    needToClose = false;
}
