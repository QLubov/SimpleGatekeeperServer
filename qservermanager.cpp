#include "qservermanager.h"
#include "gatekeeperlistener.h"
#include "actionfactory.h"
#include "logmanager.h"
#include "xmlreader.h"

void QServerManager::ConnectObjects(GatekeeperListener *listener)
{
    QObject* test = dynamic_cast<QObject*>(listener);
    if(!test)
        std::cout << "test is null" << std::endl;
    connect(test, SIGNAL(Finished(bool)), this, SLOT(OnTerminate(bool)));
    connect(test, SIGNAL(Finished(bool)), this, SIGNAL(Finished(bool)));
}

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
    QFile* scenario = new QFile(scenarioName);
    mEndPoint = new H323EndPoint();
    mServer = new GatekeeperServer(*mEndPoint, reader.ReadFile(scenario));
    ConnectObjects(mServer->GetListener());
    LogManager::Instance().clearLogs();
    LOG("Scenario " + scenarioName + " opened");
    LOG("server run!");
    delete scenario;
}

void QServerManager::OnTerminate(bool success)
{
    delete mServer;
    delete mEndPoint;
    mServer = 0;
    mEndPoint = 0;
}
