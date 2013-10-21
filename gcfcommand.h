#ifndef GCFCOMMAND_H
#define GCFCOMMAND_H
#pragma once

#include "actionmanager.h"

class GCFCommand : public Command
{
public:
    GCFCommand(int state);
    ~GCFCommand();
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, H323GatekeeperRequest *grqInfo);
    QString GetName(){return QString("  -->  GCF");}
};

#endif // GCFCOMMAND_H
