#include <QVector>
#include "logmanager.h"
#include "gatekeeperserver.h"
#include "gatekeeperlistener.h"
#include "statemachine.h"

GatekeeperServer::GatekeeperServer(H323EndPoint &endpoint, StateMachine& machine)
    : H323GatekeeperServer(endpoint)
{    
    LOG("nya!");
    PIPSocket::Address addr("192.168.0.23");
    H323TransportUDP *trans = new H323TransportUDP(endpoint, addr, H225_RAS::DefaultRasUdpPort);
    H323GatekeeperListener *listener = new GatekeeperListener(endpoint, *this, "Luba", trans, machine);
    AddListener(listener);
}


GatekeeperServer::~GatekeeperServer(void)
{
}
