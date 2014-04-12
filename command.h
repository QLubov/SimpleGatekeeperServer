#ifndef COMMAND_H
#define COMMAND_H
#pragma once

#include <QString.h>
#include <ptlib.h>
#include <h323.h>
#include <gkserver.h>
#include "enumOfStates.h"

class Command
{    
    int mState;
public:
    Command(int state);
    virtual ~Command();
    virtual H323GatekeeperRequest::Response execute(H323GatekeeperListener *, H323GatekeeperRequest* ) = 0;
    virtual QString GetName() = 0;
    virtual bool ValidateState(int state);
};

#endif // COMMAND_H
