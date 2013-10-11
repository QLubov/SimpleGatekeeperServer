#ifndef RCFCOMMAND_H
#define RCFCOMMAND_H
#include "actionmanager.h"

class RCFCommand : public Command
{
public:
    RCFCommand(int state);// : Command(state){}
    ~RCFCommand();
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, H323GatekeeperGRQ &info);
    //PString GetName();//{return "GCF";}//по ссылке!
};

#endif // RCFCOMMAND_H
