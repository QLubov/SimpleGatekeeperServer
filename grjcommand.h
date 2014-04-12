#ifndef GRJCOMMAND_H
#define GRJCOMMAND_H
#pragma once
#include "command.h"
#include "ptlib.h"
#include "h323.h"
#include "gkserver.h"

class GRJCommand : public Command
{
public:
    GRJCommand(int state);
    ~GRJCommand();
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, H323GatekeeperRequest *grqInfo);
    QString GetName(){return QString("  -->  GRJ");}
};

#endif // GRJCOMMAND_H
