#ifndef UCFCOMMAND_H
#define UCFCOMMAND_H
#include "actionmanager.h"

class UCFCommand : public Command
{
public:
    UCFCommand(int state);// : Command(state){}
    ~UCFCommand();
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info);//*/H323GatekeeperRequest *urqInfo);//тут будет нужен ррку
    QString GetName(){return QString("  -->  UCF");}//РїРѕ СЃСЃС‹Р»РєРµ!g
};

#endif // UCFCOMMAND_H
