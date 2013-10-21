#ifndef UCFCOMMAND_H
#define UCFCOMMAND_H

#include "actionmanager.h"

class UCFCommand : public Command
{
public:
    UCFCommand(int state);
    ~UCFCommand();
    H323GatekeeperRequest::Response execute(H323GatekeeperListener *listener, H323GatekeeperRequest *urqInfo);
    QString GetName(){return QString("  -->  UCF");}
};

#endif // UCFCOMMAND_H
