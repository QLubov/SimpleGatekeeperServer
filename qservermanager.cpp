#include "qservermanager.h"
#include "logmanager.h"

QServerManager::QServerManager(QObject *parent) :
    QObject(parent),
    mServer(0),
    mEndPoint(0)
{
}

void QServerManager::InitServer(const QString& scenarioName)
{
    if(mServer || mEndPoint)
    {
        LOG("Server already exists");
        return;
    }
    mEndPoint = new H323EndPoint();
    mServer = new GatekeeperServer(*mEndPoint);
    LogManager::Instance().clearLogs();
    LOG("Scenario " + scenarioName + " opened");
    LOG("server run!");
}

void QServerManager::OnTerminate(const QString &message)
{
    LOG(message);
    delete mServer;
    delete mEndPoint;
    mServer = 0;
    mEndPoint = 0;
}
