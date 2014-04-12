#ifndef GRQCOMMAND_H
#define GRQCOMMAND_H
#pragma once

#include "actionmanager.h"

class GRQCommand : public Command
{
public:
    GRQCommand(int state);
    ~GRQCommand();
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, H323GatekeeperRequest *grqInfo);
    QString GetName(){return QString("  <--  GRQ");}

};

#endif // GRQCOMMAND_H
