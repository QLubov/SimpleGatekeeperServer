#ifndef RCFCOMMAND_H
#define RCFCOMMAND_H
#include "actionmanager.h"

class RCFCommand : public Command
{
public:
    RCFCommand(int state);// : Command(state){}
    ~RCFCommand();
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info);//*/H323GatekeeperRequest *rrqInfo);//��� ����� ����� ����
    QString GetName(){return QString("  -->  RCF");}//по ссылке!g
};

#endif // RCFCOMMAND_H
