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
    if (!commands->empty())
    {
        Command *c = commands->front();
        return c->ValidateState(state);
    }
    return false;
}

H323GatekeeperRequest::Response ActionManager::ExecuteCommand(H323GatekeeperListener *listener,/* H323GatekeeperGRQ &info)//*/H323GatekeeperRequest  *info)
{
    Command *c = commands->front();
    commands->pop();

    //LogWindow& log = LogWindow::Instance();
    //log.show();
    //log.update(QString("hohoi"));
    LogManager &log = LogManager::Instance();
    log.PushLog(QString("execute command " + c->GetName()));
    return c->execute(listener, info);
}
int ActionManager::CountOfCommand()
{
    return commands->size();
}

