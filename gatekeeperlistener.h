#ifndef GATEKEEPERLISTENER_H
#define GATEKEEPERLISTENER_H
#include <ptlib.h>
#include <gkserver.h>

class GatekeeperListener
        : public H323GatekeeperListener
{
public:
    GatekeeperListener(H323EndPoint &endpoint, H323GatekeeperServer &server, const PString &gatekeeperIdentifier/*, SimpleGatekeeper *gatekeeper*/, H323Transport *transport);
    virtual ~GatekeeperListener(void);
};


#endif // GATEKEEPERLISTENER_H
