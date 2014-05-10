#ifndef GATEKEEPERSERVER_H
#define GATEKEEPERSERVER_H
#include <gkserver.h>

class GatekeeperServer:
    public H323GatekeeperServer
{   
public:
    GatekeeperServer(H323EndPoint &endpoint);
    virtual ~GatekeeperServer(void);
};

#endif // GATEKEEPERSERVER_H
