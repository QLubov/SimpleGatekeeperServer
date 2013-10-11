#ifndef RRQCOMMAND_H
#define RRQCOMMAND_H

#include "actionmanager.h"

class RRQCommand : public Command
{
public:
    RRQCommand(int state);// : Command(state){}
    ~RRQCommand();//{}
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, H323GatekeeperGRQ &info);
    //PString GetName();//{return "RRQ";}
};

#endif // RRQCOMMAND_H
