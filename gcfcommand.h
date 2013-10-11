#ifndef GCFCOMMAND_H
#define GCFCOMMAND_H
#pragma once
#include <command.h>
#include <iostream>
#include "ptlib.h"
#include "h323.h"
#include "gkserver.h"

class GCFCommand : public Command
{
    //Q_OBJECT
public:
    GCFCommand(int state);// : Command(state){}
    ~GCFCommand();
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, H323GatekeeperGRQ &info);
    //PString GetName();//{return "GCF";}//по ссылке!
};

#endif // GCFCOMMAND_H
