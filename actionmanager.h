#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H
//#include "h323.h"
//#include "gkserver.h"
#pragma once
#include "xmlreader.h"
#include <ptlib.h>
//#include "logwindow.h"

class ActionManager
{
public:
    ~ActionManager();
    static ActionManager& Instance();
    PBoolean CheckState(int state);
    H323GatekeeperRequest::Response ExecuteCommand(H323GatekeeperListener*, H323GatekeeperRequest&);
    void ParseXML(QFile*);
    enum States {GRQ = 0, GCF = 1, GRJ = 2, RRQ = 3, RCF = 4, RRJ = 5};
    int CountOfCommand();
private:
    ActionManager();
    ActionManager (const ActionManager&);
    ActionManager& operator=(const ActionManager&);
    static ActionManager *instance;

    std::queue<Command*>* commands;

};

#endif // ACTIONMANAGER_H
