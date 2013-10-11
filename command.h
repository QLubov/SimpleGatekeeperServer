#ifndef COMMAND_H
#define COMMAND_H
#pragma once
#include <ptlib.h>
#include <h323.h>
#include <gkserver.h>
//#include <QString.h>
//#include "actionmanager.h"

class Command
{
    //Q_OBJECT
    int mState;
public:
    Command(int state);
    virtual ~Command();
    virtual H323GatekeeperRequest::Response execute(H323GatekeeperListener *, H323GatekeeperGRQ &) = 0;
    //virtual PString GetName() = 0;
    virtual bool ValidateState(int state);

};

#endif // COMMAND_H
