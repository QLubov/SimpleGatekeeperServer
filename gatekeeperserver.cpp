#include <QVector>
#include "logmanager.h"
#include "gatekeeperserver.h"
#include "gatekeeperlistener.h"
#include "statemachine.h"

GatekeeperServer::GatekeeperServer(H323EndPoint &endpoint, StateMachine& machine)
    : H323GatekeeperServer(endpoint)
{    
    PIPSocket::Address addr("192.168.0.23");
    mTransport = new H323TransportUDP(endpoint, addr, H225_RAS::DefaultRasUdpPort);
    mListener = new GatekeeperListener(endpoint, *this, "Luba", mTransport, machine);
    AddListener(mListener);
}


GatekeeperServer::~GatekeeperServer(void)
{
   // RemoveListener(mListener);
    //delete mListener;
    //delete mTransport;
}
