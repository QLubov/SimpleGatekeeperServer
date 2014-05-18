#ifndef GATEKEEPERLISTENER_H
#define GATEKEEPERLISTENER_H
#include <QVector>
#include "statemachine.h"
#include <ptlib.h>
#include <gkserver.h>

class GatekeeperListener
        : public H323GatekeeperListener
{
    Trigger GetTrigger(unsigned int pduTag);
    StateMachine mStateMachine;
public:
    GatekeeperListener(H323EndPoint &endpoint, H323GatekeeperServer &server, const PString &gatekeeperIdentifier, H323Transport *transport, StateMachine& machine);
    virtual ~GatekeeperListener(void);
    virtual PBoolean HandleTransaction (const PASN_Object &rawPDU);
};

#endif // GATEKEEPERLISTENER_H
