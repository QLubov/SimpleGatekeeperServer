#ifndef GRQCOMMAND_H
#define GRQCOMMAND_H
#pragma once
//#include <command.h>
//#include "ptlib.h"
//#include "h323.h"
//#include "gkserver.h"
//#include <iostream>
#include "actionmanager.h"
//#include "logwindow.h"

class GRQCommand : public Command
{
    //Q_OBJECT
public:
    GRQCommand(int state);// : Command(state){}
    ~GRQCommand();//{}
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info);//*/H323GatekeeperRequest *grqInfo);
    QString GetName(){return QString("  <--  GRQ");}

};

#endif // GRQCOMMAND_H
