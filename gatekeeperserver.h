#ifndef GATEKEEPERSERVER_H
#define GATEKEEPERSERVER_H

#include "gatekeeperlistener.h"

class GatekeeperServer:
    public H323GatekeeperServer
{
    virtual void Configure();
    virtual void Terminate();
    std::vector<PIPSocket::Address> mGKAddrs;
    std::vector<WORD> mGKPorts;
    void GetTransportsByReference(H323EndPoint *, vector<H323TransportUDP *> &);
    void RemoveTransports(vector<H323TransportUDP *> &);
    list<GatekeeperListener*> listeners;
    bool mFinished;
public:
    GatekeeperServer(H323EndPoint &endpoint);
    virtual ~GatekeeperServer(void);

    virtual H323GatekeeperRequest::Response OnDiscovery (H323GatekeeperGRQ &info);
    virtual H323GatekeeperRequest::Response OnRegistration(H323GatekeeperRRQ & info);

    bool IsFinished();
    void Finish();
};

#endif // GATEKEEPERSERVER_H
