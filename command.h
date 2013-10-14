#ifndef COMMAND_H
#define COMMAND_H
#pragma once
#include <QString.h>
#include <ptlib.h>
#include <h323.h>
#include <gkserver.h>
#include <enumOfStates.h>
//#include "actionmanager.h"
//#include <logmanager.h>
class Command
{
    //Q_OBJECT
    int mState;
public:
    Command(int state);
    virtual ~Command();
    virtual H323GatekeeperRequest::Response execute(H323GatekeeperListener *, /*H323GatekeeperGRQ&)=0;//*/H323GatekeeperRequest* ) = 0;//тут по идее √ейткипер–еквест, но там дальше пич€лька в конкретных командах
    virtual QString GetName() = 0;
    virtual bool ValidateState(int state);

};

#endif // COMMAND_H
