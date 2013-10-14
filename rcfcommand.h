#ifndef RCFCOMMAND_H
#define RCFCOMMAND_H
#include "actionmanager.h"

class RCFCommand : public Command
{
public:
    RCFCommand(int state);// : Command(state){}
    ~RCFCommand();
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info);//*/H323GatekeeperRequest *rrqInfo);//тут будет нужен ррку
    QString GetName(){return QString("  -->  RCF");}//РїРѕ СЃСЃС‹Р»РєРµ!g
};

#endif // RCFCOMMAND_H
