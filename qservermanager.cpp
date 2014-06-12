#include "qservermanager.h"
#include "gatekeeperlistener.h"
#include "objectfactory.h"
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
    mEndPoint(0),
    mScenario(0),
    mOptions(0)
{
    REG(Scenario);
    ObjectFactory::AddClass("Options", new MetaCreator<OptionManager::Options>);
    REG(SendGCF);
    REG(SendRCF);
    REG(SendUCF);
    REG(SendACF);
    REG(Delay);
}

bool QServerManager::PrepareTestCase(const QString& scenarioName)
{
    XMLReader reader(scenarioName);
    if(!reader.IsValid())
        return false;
    mScenario = (Scenario*)reader.Parse("Scenario");
    mOptions = (OptionManager::Options*)reader.Parse("Options");
    if(!mScenario || !mOptions)
        return false;
    OptionManager::Instance().SetOptionsMap(mOptions->GetMap());
    return true;
}

void QServerManager::InitServer(const QString& scenarioName)
{
    if(mServer || mEndPoint)
    {
        LOG("Server already exists");
        return;
    }

    if(!PrepareTestCase(scenarioName))
    {
        //LOG();
        emit Finished(false);
        return;
    }

    mEndPoint = new H323EndPoint();
    mServer = new GatekeeperServer(*mEndPoint, mScenario->GetStateMachine());
    ConnectObjects(mServer->GetListener());
    LogManager::Instance().clearLogs();
    LOG("Scenario " + scenarioName + " is opened");
    LOG("server run!");
}

void QServerManager::OnTerminate(bool success)
{
    delete mServer;
    delete mEndPoint;
    mServer = 0;
    mEndPoint = 0;
    delete mScenario;
    delete mOptions;
}
