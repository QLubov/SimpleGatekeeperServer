#include "gatekeeperlistener.h"

GatekeeperListener::GatekeeperListener(H323EndPoint &endpoint, H323GatekeeperServer &server, const PString &gatekeeperIdentifier, H323Transport *transport)
: H323GatekeeperListener(endpoint, server, gatekeeperIdentifier, transport)
{    
    mRegistrationReceived = false;
}

GatekeeperListener::~GatekeeperListener(void)
{
    StopChannel();
}
H323GatekeeperRequest::Response GatekeeperListener::OnDiscovery (H323GatekeeperGRQ & info)
{
    std::cout<<"onDiscovery in listener!"<<std::endl;
    LogManager &log = LogManager::Instance();
    log.PushLog(QString("Establish connection with " + info.GetReplyAddress().GetHostName()));

    ActionManager &mng = ActionManager::Instance();
    if(mng.CheckState(GRQ))
        return mng.ExecuteCommand(this, &info);
    else
    {
        std::cout<<"Err in onDiscovery!"<<std::endl;

        log.PushLog(QString("Error: Received GRQ instead " + mng.GetCommandName()));

        mng.deleteScenario();//the commands queue should be erased for exiting
        return H323GatekeeperRequest::Reject;
    }


}

void GatekeeperListener::Foo(ActionManager &mng)
{
    std::cout<<"Err in onRegistration!"<<std::endl;
    LogManager &log = LogManager::Instance();
    log.PushLog(QString("Error: Received RRQ instead " + mng.GetCommandName()));
    mng.deleteScenario();
}

H323GatekeeperRequest::Response GatekeeperListener::OnRegistration(H323GatekeeperRRQ & info)
 {
    std::cout<<"H323GatekeeperListener::OnRegistration"<<std::endl;    

    ActionManager &mng = ActionManager::Instance();
    if(mng.CheckState(RRQ))
    {        
        mRegistrationReceived = true;
        return mng.ExecuteCommand(this, &info);
    }
    else
    {
        if(!mRegistrationReceived)
        {
            Foo(mng);
            return H323GatekeeperRequest::Reject;
        }
        else
        {            
            return OnRegistrationInfo(info);//ping
        }        
    }
}

 H323GatekeeperRequest::Response GatekeeperListener::OnUnregistration(H323GatekeeperURQ & info)
  {       
    std::cout<<"H323GatekeeperListener::OnUnregistration"<<std::endl;

    ActionManager &mng = ActionManager::Instance();
    if(mng.CheckState(URQ))
        return mng.ExecuteCommand(this, &info);
    else
    {
        std::cout<<"Err in onUnregistration!"<<std::endl;
        LogManager &log = LogManager::Instance();
        log.PushLog(QString("Error: Received URQ instead " + mng.GetCommandName()));
        mng.deleteScenario();
        return H323GatekeeperRequest::Reject;
    }    
  }


H323GatekeeperRequest::Response GatekeeperListener::OnRegistrationInfo(H323GatekeeperRRQ & info)
{
    std::cout<<" OnRegistrationInfo!"<<std::endl;
    H323GatekeeperRequest::Response response = gatekeeper.OnRegistration(info);
    if (response != H323GatekeeperRequest::Confirm)
    {
        std::cout<<" Err in RRQCommand!"<<std::endl;
        return H323GatekeeperRequest::Reject;

    }

    if (!info.rrq.m_keepAlive) {
      PSafePtr<H323RegisteredEndPoint> lock(info.endpoint, PSafeReadWrite);
      H235Authenticators authenticators = info.endpoint->GetAuthenticators();
      for (PINDEX i = 0; i < authenticators.GetSize(); i++) {
        H235Authenticator & authenticator = authenticators[i];
        if (authenticator.UseGkAndEpIdentifiers()) {
          authenticator.SetRemoteId(info.endpoint->GetIdentifier());
          authenticator.SetLocalId(GetIdentifier());
        }
      }
    }
  std::cout<<"H323GatekeeperListener::OnRegistration confirm!"<<std::endl;
    return H323GatekeeperRequest::Confirm;
}

bool GatekeeperListener::HandleTransaction(const PASN_Object &rawPDU)
{
    std::cout<<"HandleTransaction!!"<<std::endl;
    const H323RasPDU & pdu = (const H323RasPDU &)rawPDU;

      switch (pdu.GetTag()) {
        case H225_RasMessage::e_gatekeeperRequest :
          if (SendCachedResponse(pdu))
            return FALSE;
          OnReceiveGatekeeperRequest(pdu, pdu);
          break;

        case H225_RasMessage::e_gatekeeperConfirm :
          return OnReceiveGatekeeperConfirm(pdu, pdu);

        case H225_RasMessage::e_gatekeeperReject :
          return OnReceiveGatekeeperReject(pdu, pdu);

        case H225_RasMessage::e_registrationRequest :
          if (SendCachedResponse(pdu))
            return FALSE;
          OnReceiveRegistrationRequest(pdu, pdu);
          break;

        case H225_RasMessage::e_registrationConfirm :
          return OnReceiveRegistrationConfirm(pdu, pdu);

        case H225_RasMessage::e_registrationReject :
          return OnReceiveRegistrationReject(pdu, pdu);

        case H225_RasMessage::e_unregistrationRequest :
          if (SendCachedResponse(pdu))
            return FALSE;
          OnReceiveUnregistrationRequest(pdu, pdu);
          break;

        //case H225_RasMessage::e_unregistrationConfirm :
        //  return OnReceiveUnregistrationConfirm(pdu, pdu);

        //case H225_RasMessage::e_unregistrationReject :
        //  return OnReceiveUnregistrationReject(pdu, pdu);

        case H225_RasMessage::e_admissionRequest :
          if (SendCachedResponse(pdu))
            return FALSE;
          OnReceiveAdmissionRequest(pdu, pdu);
          break;

        case H225_RasMessage::e_admissionConfirm :
          return OnReceiveAdmissionConfirm(pdu, pdu);

        case H225_RasMessage::e_admissionReject :
          return OnReceiveAdmissionReject(pdu, pdu);

        case H225_RasMessage::e_bandwidthRequest :
          if (SendCachedResponse(pdu))
            return FALSE;
          OnReceiveBandwidthRequest(pdu, pdu);
          break;

        //case H225_RasMessage::e_bandwidthConfirm :
        //  return OnReceiveBandwidthConfirm(pdu, pdu);

        //case H225_RasMessage::e_bandwidthReject :
        //  return OnReceiveBandwidthReject(pdu, pdu);

        case H225_RasMessage::e_disengageRequest :
          if (SendCachedResponse(pdu))
            return FALSE;
          OnReceiveDisengageRequest(pdu, pdu);
          break;

        //case H225_RasMessage::e_disengageConfirm :
        //  return OnReceiveDisengageConfirm(pdu, pdu);

        //case H225_RasMessage::e_disengageReject :
        //  return OnReceiveDisengageReject(pdu, pdu);

        case H225_RasMessage::e_locationRequest :
          if (SendCachedResponse(pdu))
            return FALSE;
          OnReceiveLocationRequest(pdu, pdu);
          break;

        case H225_RasMessage::e_locationConfirm :
          return OnReceiveLocationConfirm(pdu, pdu);

        case H225_RasMessage::e_locationReject :
          return OnReceiveLocationReject(pdu, pdu);

        case H225_RasMessage::e_infoRequest :
          if (SendCachedResponse(pdu))
            return FALSE;
          OnReceiveInfoRequest(pdu, pdu);
          break;

        case H225_RasMessage::e_infoRequestResponse :
          return OnReceiveInfoRequestResponse(pdu, pdu);

        case H225_RasMessage::e_nonStandardMessage :
          OnReceiveNonStandardMessage(pdu, pdu);
          break;

        case H225_RasMessage::e_unknownMessageResponse :
          OnReceiveUnknownMessageResponse(pdu, pdu);
          break;

        case H225_RasMessage::e_requestInProgress :
          return OnReceiveRequestInProgress(pdu, pdu);

        case H225_RasMessage::e_resourcesAvailableIndicate :
          if (SendCachedResponse(pdu))
            return FALSE;
          OnReceiveResourcesAvailableIndicate(pdu, pdu);
          break;

        //case H225_RasMessage::e_resourcesAvailableConfirm :
        //  return OnReceiveResourcesAvailableConfirm(pdu, pdu);

        case H225_RasMessage::e_infoRequestAck :
          return OnReceiveInfoRequestAck(pdu, pdu);

        case H225_RasMessage::e_infoRequestNak :
          return OnReceiveInfoRequestNak(pdu, pdu);

        case H225_RasMessage::e_serviceControlIndication :
          if (SendCachedResponse(pdu))
            return FALSE;
          OnReceiveServiceControlIndication(pdu, pdu);
          break;

        case H225_RasMessage::e_serviceControlResponse :
          return OnReceiveServiceControlResponse(pdu, pdu);

        default :
          OnReceiveUnknown(pdu);
      }

      return FALSE;
}

