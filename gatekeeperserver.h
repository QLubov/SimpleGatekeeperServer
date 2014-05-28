#ifndef GATEKEEPERSERVER_H
#define GATEKEEPERSERVER_H
#include <gkserver.h>

class StateMachine;
class GatekeeperListener;

class GatekeeperServer:
    public H323GatekeeperServer
{   
    GatekeeperListener *mListener;
    H323TransportUDP *mTransport;
public:
    GatekeeperServer(H323EndPoint &endpoint, StateMachine& machine);
    virtual ~GatekeeperServer(void);
    GatekeeperListener* GetListener() const {return mListener;}
};

#endif // GATEKEEPERSERVER_H
