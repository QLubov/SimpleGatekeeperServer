#include "actionmanager.h"

ActionManager::ActionManager()
{
    success = true;
}

ActionManager::~ActionManager()
{
}

void ActionManager::ParseXML(QFile * file)
{
    success = true;
    XMLReader xml;
    commands = xml.ReadFile(file);    
}

/*static*/  ActionManager& ActionManager::Instance()
{
    static ActionManager instance;
    return instance;
}

PBoolean ActionManager::CheckState(int state)
{
    if (!commands.empty())
    {
        Command *c = commands.front();
        return c->ValidateState(state);
    }
    return false;
}

H323GatekeeperRequest::Response ActionManager::ExecuteCommand(H323GatekeeperListener *listener,H323GatekeeperRequest  *info)
{
    Command *c = commands.front();
    commands.pop();

    LogManager &log = LogManager::Instance();
    log.PushLog(c->GetName());
    return c->execute(listener, info);
}
int ActionManager::GetCountOfCommand()
{
    return commands.size();
}

void ActionManager::deleteScenario()
{
    success = false;
    int size = commands.size();
    for(int i = 0; i < size; i++)
        commands.pop();
}

QString ActionManager::GetCommandName()
{
    if(commands.empty())
        return QString("");
    return commands.front()->GetName();
}
