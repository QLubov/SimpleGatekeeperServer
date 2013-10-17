#ifndef GATEKEEPERLISTENER_H
#define GATEKEEPERLISTENER_H
#pragma once
//#include <ptlib.h>
//#include "h323.h"
//#include "gkserver.h"
#include "actionmanager.h"
//#include "logwindow.h"
#include "rcfcommand.h"

class GatekeeperListener
        : public H323GatekeeperListener
{
public:
    GatekeeperListener(H323EndPoint &endpoint, H323GatekeeperServer &server, const PString &gatekeeperIdentifier/*, SimpleGatekeeper *gatekeeper*/, H323Transport *transport);
    virtual ~GatekeeperListener(void);
    virtual H323GatekeeperRequest::Response OnDiscovery (H323GatekeeperGRQ & info) ;
    virtual H323GatekeeperRequest::Response OnRegistration(H323GatekeeperRRQ & info);
    H323GatekeeperRequest::Response OnUnregistration(H323GatekeeperURQ & info);
private:
    bool flag;
    H323GatekeeperRequest::Response OnRegistrationInfo(H323GatekeeperRRQ & info);
};


#endif // GATEKEEPERLISTENER_H
