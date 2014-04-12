#ifndef RCFCOMMAND_H
#define RCFCOMMAND_H

#include "actionmanager.h"

class RCFCommand : public Command
{
public:
    RCFCommand(int state);
    ~RCFCommand();
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, H323GatekeeperRequest *rrqInfo);
    QString GetName(){return QString("  -->  RCF");}
};

#endif // RCFCOMMAND_H
