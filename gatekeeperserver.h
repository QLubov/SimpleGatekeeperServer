#ifndef GATEKEEPERSERVER_H
#define GATEKEEPERSERVER_H
#pragma once
//#include "h323.h"
//#include "gkserver.h"
#include "gatekeeperlistener.h"

class GatekeeperServer:
    public H323GatekeeperServer
{
    virtual void Configure();
    virtual void Terminate();
    std::vector<PIPSocket::Address> mGKAddrs;
    std::vector<WORD> mGKPorts;
    void	GetTransportsByReference(H323EndPoint *, vector<H323TransportUDP *> &);
    void	RemoveTransports(vector<H323TransportUDP *> &);
    list<GatekeeperListener*> listeners;
public:
    GatekeeperServer(H323EndPoint &endpoint/*, H323Transport *transport*/);
    virtual ~GatekeeperServer(void);

    //virtual H323GatekeeperRequest::Response OnDiscovery (H323GatekeeperGRQ &info);
    virtual H323GatekeeperRequest::Response OnRegistration(H323GatekeeperRRQ & info);
    //virtual H323GatekeeperRequest::Response OnAdmission(H323GatekeeperARQ & info);
    H323GatekeeperRequest::Response OnRegistrationInfo(H323GatekeeperRRQ & info);
};

#endif // GATEKEEPERSERVER_H
