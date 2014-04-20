#include "qserverthread.h"

QServerThread::QServerThread(const QString& scenarioName, QObject *parent) :
    QThread(parent),
    needToClose(true)
{
    QFile file(scenarioName);
    ActionManager &mng = ActionManager::Instance();
    mng.ParseXML(&file);
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}

void QServerThread::run()
{
    H323EndPoint ep;   
    GatekeeperServer serv(ep);
    LogManager &log = LogManager::Instance();
    log.clearLogs();
    log.PushLog(QString("server run!"));
    ActionManager &mng = ActionManager::Instance();
    while(needToClose && mng.GetCountOfCommand())
    {
    }

    if(mng.IsSuccessed() && needToClose)
        log.PushLog(QString("Scenario was successfully finished"));
    else
       log.PushLog(QString("server stop"));    
}
void QServerThread::end()
{    
    needToClose = false;
}
