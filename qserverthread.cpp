#include "qserverthread.h"

QServerThread::QServerThread(const QString& scenarioName, QObject *parent) :
    QThread(parent)
{
    QFile file(scenarioName);
    ActionManager &mng = ActionManager::Instance();
    mng.ParseXML(&file);
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}

void QServerThread::run()
{
    H323EndPoint ep;
    mServer = new GatekeeperServer(ep);
    LogManager::Instance().clearLogs();

    LOG("server run!");

    while(!mServer->IsFinished());
    cout<<"delete server"<<endl;
    delete mServer;
}
void QServerThread::StopServer()
{    
    mServer->Finish();
}
