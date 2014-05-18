#ifndef GATEKEEPERSERVER_H
#define GATEKEEPERSERVER_H
#include <gkserver.h>

class StateMachine;

class GatekeeperServer:
    public H323GatekeeperServer
{   
public:
    GatekeeperServer(H323EndPoint &endpoint, StateMachine& machine);
    virtual ~GatekeeperServer(void);

};

#endif // GATEKEEPERSERVER_H
