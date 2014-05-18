#include "qservermanager.h"
#include "actionfactory.h"
#include "logmanager.h"
#include "xmlreader.h"

QServerManager::QServerManager(QObject *parent) :
    QObject(parent),
    mServer(0),
    mEndPoint(0)
{
    REG(SendGCF);
    REG(SendRCF);
    REG(SendUCF);
    REG(SendACF);
    REG(Delay);
}

void QServerManager::InitServer(const QString& scenarioName)
{
    if(mServer || mEndPoint)
    {
        LOG("Server already exists");
        return;
    }
    XMLReader reader;
    mEndPoint = new H323EndPoint();
    mServer = new GatekeeperServer(*mEndPoint, StateMachine(reader.ReadFile(new QFile(scenarioName))));
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
