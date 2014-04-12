#ifndef URJCOMMAND_H
#define URJCOMMAND_H

#include "command.h"
#include "ptlib.h"
#include "h323.h"
#include "gkserver.h"

class URJCommand : public Command
{
public:
    URJCommand(int state);
    ~URJCommand();
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, H323GatekeeperRequest *urqInfo);
    QString GetName(){return QString("  -->  URJ");}
};

#endif // URJCOMMAND_H
