#include "gatekeeperlistener.h"

GatekeeperListener::GatekeeperListener(H323EndPoint &endpoint, H323GatekeeperServer &server, const PString &gatekeeperIdentifier, H323Transport *transport)
: H323GatekeeperListener(endpoint, server, gatekeeperIdentifier, transport)
{
}

GatekeeperListener::~GatekeeperListener(void)
{
    StopChannel();
}
