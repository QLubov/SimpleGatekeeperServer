#include"statemachine.h"
#include "logmanager.h"
#include "gatekeeperlistener.h"


Trigger GatekeeperListener::GetTrigger(unsigned int pduTag)
{
    switch(pduTag)
    {
        case H225_RasMessage::e_gatekeeperRequest :
              return tGRQ;
              break;

        case H225_RasMessage::e_registrationRequest :
          return tRRQ;
          break;

        case H225_RasMessage::e_unregistrationRequest :
          return tURQ;
          break;

        case H225_RasMessage::e_admissionRequest :
          return tARQ;
          break;

        case H225_RasMessage::e_bandwidthRequest :
          return tBRQ;
          break;

        case H225_RasMessage::e_locationRequest :
          return tLRQ;
          break;

        case H225_RasMessage::e_disengageRequest :
        case H225_RasMessage::e_infoRequest :
        case H225_RasMessage::e_nonStandardMessage :
        case H225_RasMessage::e_unknownMessageResponse :
        case H225_RasMessage::e_resourcesAvailableIndicate :
        case H225_RasMessage::e_resourcesAvailableConfirm :
        case H225_RasMessage::e_infoRequestAck :
        case H225_RasMessage::e_infoRequestNak :
        case H225_RasMessage::e_serviceControlIndication :
        case H225_RasMessage::e_serviceControlResponse :
        default :
          return tINVALID;
      }
}

GatekeeperListener::GatekeeperListener(H323EndPoint &endpoint, H323GatekeeperServer &server, const PString &gatekeeperIdentifier, H323Transport *transport, StateMachine& machine)
: QObject(0),
  H323GatekeeperListener(endpoint, server, gatekeeperIdentifier, transport),
  mStateMachine(machine)
{
}

GatekeeperListener::~GatekeeperListener(void)
{
    StopChannel();
}

PBoolean GatekeeperListener::HandleTransaction(const PASN_Object &rawPDU)
{
    const H323RasPDU & pdu = (const H323RasPDU &)rawPDU;


    Trigger trigger = GetTrigger(pdu.GetTag());
    if (!mStateMachine.DoTransition(trigger, this, pdu))
    {
        LOG("Server successefully failed " + TriggerToString(trigger) + " received");
        EmitFinish(false);
    }
    return true;
}

void GatekeeperListener::EmitFinish(bool success)
{
    emit Finished(success);
}
