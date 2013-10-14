#ifndef RRJCOMMAND_H
#define RRJCOMMAND_H
//#include "actionmanager.h"
#include <command.h>
#include "ptlib.h"
#include "h323.h"
#include "gkserver.h"
class RRJCommand : public Command
{
public:
    RRJCommand(int state);// : Command(state){}
    ~RRJCommand();
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info);//*/H323GatekeeperRequest *rrqInfo);//тут будет нужен ррку
    QString GetName(){return QString("  -->  RRJ");}//РїРѕ СЃСЃС‹Р»РєРµ!g
};

#endif // RRJCOMMAND_H
