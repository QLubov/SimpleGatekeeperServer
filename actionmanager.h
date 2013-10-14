#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H
//#include "h323.h"
//#include "gkserver.h"
#pragma once
#include "xmlreader.h"
#include <ptlib.h>
//#include "logwindow.h"
#include "logmanager.h"
#include <enumOfStates.h>
class ActionManager// : public QObject
{
public:
    ~ActionManager();
    static ActionManager& Instance();
    PBoolean CheckState(int state);
    H323GatekeeperRequest::Response ExecuteCommand(H323GatekeeperListener*, /*H323GatekeeperGRQ&);//*/H323GatekeeperRequest*);
    void ParseXML(QFile*);
    //enum States {};
    int CountOfCommand();
private:
    ActionManager();
    ActionManager (const ActionManager&);
    ActionManager& operator=(const ActionManager&);
    static ActionManager *instance;

    std::queue<Command*>* commands;
/*signals:
    void error();*/
};

#endif // ACTIONMANAGER_H
