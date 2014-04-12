#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H
#pragma once

#include "xmlreader.h"
#include <ptlib.h>
#include "logmanager.h"
#include "enumOfStates.h"

class ActionManager
{ 
public:
    ~ActionManager();
    static ActionManager& Instance();
    PBoolean CheckState(int state);
    H323GatekeeperRequest::Response ExecuteCommand(H323GatekeeperListener*, H323GatekeeperRequest*);
    void ParseXML(QFile*);
    int GetCountOfCommand();
    void deleteScenario();
    QString GetCommandName();
    PBoolean IsSuccessed(){return success;}
private:
    ActionManager();
    ActionManager (const ActionManager&);
    ActionManager& operator=(const ActionManager&);    
    bool success;
    std::queue<Command*> commands;
};

#endif // ACTIONMANAGER_H
