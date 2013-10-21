#ifndef RRQCOMMAND_H
#define RRQCOMMAND_H

#include "actionmanager.h"

class RRQCommand : public Command
{
public:
    RRQCommand(int state);
    ~RRQCommand();
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, H323GatekeeperRequest *rrqInfo);
    QString GetName(){return QString("  <--  RRQ");}
};

#endif // RRQCOMMAND_H
