#ifndef URJCOMMAND_H
#define URJCOMMAND_H
#include <command.h>
#include "ptlib.h"
#include "h323.h"
#include "gkserver.h"

class URJCommand : public Command
{
public:
    URJCommand(int state);// : Command(state){}
    ~URJCommand();
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info);//*/H323GatekeeperRequest *urqInfo);//тут будет нужен ррку
    QString GetName(){return QString("  -->  URJ");}//РїРѕ СЃСЃС‹Р»РєРµ!g
};

#endif // URJCOMMAND_H
