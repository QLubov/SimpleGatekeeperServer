#ifndef DELAYCOMMAND_H
#define DELAYCOMMAND_H
#include "actionmanager.h"

class DelayCommand : public Command
{
    int delay;
public:
    DelayCommand(int state, int seconds);
    ~DelayCommand();//{}
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info);//*/H323GatekeeperRequest *grqInfo);
    QString GetName(){return QString("  -- Delay " + QString::number(delay) + " ms --");}

};

#endif // DELAYCOMMAND_H
