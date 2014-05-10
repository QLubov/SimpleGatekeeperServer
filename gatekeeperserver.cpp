#include "logmanager.h"
#include "gatekeeperserver.h"
#include "gatekeeperlistener.h"
GatekeeperServer::GatekeeperServer(H323EndPoint &endpoint)
    : H323GatekeeperServer(endpoint)
{    
    LOG("nya!");
    PIPSocket::Address addr("192.168.0.23");
    H323TransportUDP *trans = new H323TransportUDP(endpoint, addr, H225_RAS::DefaultRasUdpPort);
    H323GatekeeperListener *listener = new H323GatekeeperListener(endpoint, *this, "Luba", trans);
    AddListener(listener);
}


GatekeeperServer::~GatekeeperServer(void)
{
}
