#ifndef GCFCOMMAND_H
#define GCFCOMMAND_H
#pragma once
#include <command.h>
#include <iostream>
#include "ptlib.h"
#include "h323.h"
#include "gkserver.h"

class GCFCommand : public Command
{
    //Q_OBJECT
public:
    GCFCommand(int state);// : Command(state){}
    ~GCFCommand();
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info);//*/H323GatekeeperRequest *grqInfo);//тут нужен грку
    QString GetName(){return QString("  -->  GCF");}//РїРѕ СЃСЃС‹Р»РєРµ!
};

#endif // GCFCOMMAND_H
