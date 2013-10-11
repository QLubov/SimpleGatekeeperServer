#include "actionmanager.h"

ActionManager *ActionManager::instance = 0;

ActionManager::ActionManager()
{
}

ActionManager::~ActionManager()
{
}

void ActionManager::ParseXML(QFile * file)
{
    //LogWindow& log = LogWindow::Instance();
    //log.show();
    //log.update(QString("start parsing"));
    XMLReader xml;
    commands = xml.ReadFile(file);
    //log.update(QString("end parsing"));
}

ActionManager& ActionManager::Instance()
{
    if(!instance)
        instance = new ActionManager();
    return *instance;
}

PBoolean ActionManager::CheckState(int state)
{
    Command *c = commands->front();
    return c->ValidateState(state);
}

H323GatekeeperRequest::Response ActionManager::ExecuteCommand(H323GatekeeperListener *listener, H323GatekeeperRequest &info)
{
    Command *c = commands->front();
    commands->pop();

    //LogWindow& log = LogWindow::Instance();
    //log.show();
    //log.update(QString("hohoi"));
    return c->execute(listener, info);
}
int ActionManager::CountOfCommand()
{
    return commands->size();
}

