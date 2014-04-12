#ifndef RRJCOMMAND_H
#define RRJCOMMAND_H

#include "command.h"
#include "ptlib.h"
#include "h323.h"
#include "gkserver.h"
class RRJCommand : public Command
{
public:
    RRJCommand(int state);
    ~RRJCommand();
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, H323GatekeeperRequest *rrqInfo);
    QString GetName(){return QString("  -->  RRJ");}
};

#endif // RRJCOMMAND_H
