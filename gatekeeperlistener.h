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
    //friend H323GatekeeperRequest::Response GCFCommand::execute(H323GatekeeperListener *listener, H323GatekeeperGRQ &info);
    //bool OnReceiveGatekeeperRequest (const H323RasPDU &, const H225_GatekeeperRequest &);
    virtual H323GatekeeperRequest::Response OnRegistration(H323GatekeeperRRQ & info);
    H323GatekeeperRequest::Response OnUnregistration(H323GatekeeperURQ & info);
private:
    H323GatekeeperRequest::Response OnRegistrationInfo(H323GatekeeperRRQ & info);
    //bool HandleTransaction(const PASN_Object & rawPDU);
};


#endif // GATEKEEPERLISTENER_H
