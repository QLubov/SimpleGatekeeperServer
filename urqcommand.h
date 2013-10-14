#ifndef URQCOMMAND_H
#define URQCOMMAND_H
#include "actionmanager.h"

class URQCommand : public Command
{
public:
    URQCommand(int state);// : Command(state){}
    ~URQCommand();//{}
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info);//*/H323GatekeeperRequest *urqInfo);
    QString GetName(){return QString("  <--  URQ");}
};

#endif // URQCOMMAND_H
