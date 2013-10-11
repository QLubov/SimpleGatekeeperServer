#include "gatekeeperlistener.h"

GatekeeperListener::GatekeeperListener(H323EndPoint &endpoint, H323GatekeeperServer &server, const PString &gatekeeperIdentifier/*, SimpleGatekeeper *gatekeeper*/, H323Transport *transport)
: H323GatekeeperListener(endpoint, server, gatekeeperIdentifier, transport)
{
}

GatekeeperListener::~GatekeeperListener(void)
{
}
H323GatekeeperRequest::Response GatekeeperListener::OnDiscovery (H323GatekeeperGRQ & info)
{
    std::cout<<"onDiscovery in listener!"<<std::endl;


    ActionManager &mng = ActionManager::Instance();
    if(mng.CheckState(0))
        return mng.ExecuteCommand(this, info);
    else
    {
        std::cout<<"Err in onDiscovery!"<<std::endl;

        //LogWindow & log = LogWindow::Instance();
        //log.update(QString("Err in onDiscovery!"));
    }


}

/*bool SimpleGatekeeperListener::OnReceiveGatekeeperRequest (const H323RasPDU &pdu, const H225_GatekeeperRequest &grq)
{
    std::cout<<"in on recieve GRQ"<<std::endl;
     H323GatekeeperGRQ * info = new H323GatekeeperGRQ(*this, pdu);
   if (!info->HandlePDU())
     delete info;
    return false;
}*/

/* H323GatekeeperRequest::Response GatekeeperListener::OnRegistration(H323GatekeeperRRQ & info)
 {
   PTRACE_BLOCK("H323GatekeeperListener::OnRegistration");
    std::cout<<"H323GatekeeperListener::OnRegistration"<<std::endl;

   if (info.rrq.HasOptionalField(H225_RegistrationRequest::e_endpointIdentifier))
     info.endpoint = gatekeeper.FindEndPointByIdentifier(info.rrq.m_endpointIdentifier);

   if (!info.CheckGatekeeperIdentifier())
   {
       std::cout<<"H323GatekeeperListener::OnRegistration reject!"<<std::endl;
     return H323GatekeeperRequest::Reject;
   }

   if (info.rrq.m_protocolIdentifier.GetSize() != 6 || info.rrq.m_protocolIdentifier[5] < 2) {
     info.SetRejectReason(H225_RegistrationRejectReason::e_invalidRevision);
     PTRACE(2, "RAS\tRRQ rejected, version 1 not supported");
     std::cout<<"H323GatekeeperListener::OnRegistration reject!"<<std::endl;
     return H323GatekeeperRequest::Reject;
   }

   H323GatekeeperRequest::Response response = gatekeeper.OnRegistration(info);
   if (response != H323GatekeeperRequest::Confirm)
   {
       std::cout<<"H323GatekeeperListener::OnRegistration response!"<<std::endl;
     return response;
   }

   // Adjust the authenticator remote ID to endpoint ID
   if (!info.rrq.m_keepAlive) {
     PSafePtr<H323RegisteredEndPoint> lock(info.endpoint, PSafeReadWrite);
     H235Authenticators authenticators = info.endpoint->GetAuthenticators();
     for (PINDEX i = 0; i < authenticators.GetSize(); i++) {
       H235Authenticator & authenticator = authenticators[i];
       if (authenticator.UseGkAndEpIdentifiers()) {
         authenticator.SetRemoteId(info.endpoint->GetIdentifier());
         authenticator.SetLocalId(gatekeeperIdentifier);
       }
     }
   }
 std::cout<<"H323GatekeeperListener::OnRegistration confirm!"<<std::endl;
   return H323GatekeeperRequest::Confirm;
 }*/

 /*bool GatekeeperListener::HandleTransaction(const PASN_Object & rawPDU)
 {
   const H323RasPDU & pdu = (const H323RasPDU &)rawPDU;
   //std::cout<<"in HandleTransaction!!"<<std::endl;
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

     case H225_RasMessage::e_unregistrationConfirm :
       //return OnReceiveUnregistrationConfirm(pdu, pdu);
         return OnReceiveUnregistrationConfirm(pdu);

     case H225_RasMessage::e_unregistrationReject :
       return OnReceiveUnregistrationReject(pdu/*, pdu*//*);

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

     case H225_RasMessage::e_bandwidthConfirm :
       return OnReceiveBandwidthConfirm(pdu/*, pdu*//*);

     case H225_RasMessage::e_bandwidthReject :
       return OnReceiveBandwidthReject(pdu/*, pdu*//*);

     case H225_RasMessage::e_disengageRequest :
       if (SendCachedResponse(pdu))
         return FALSE;
       OnReceiveDisengageRequest(pdu, pdu);
       break;

     case H225_RasMessage::e_disengageConfirm :
       return OnReceiveDisengageConfirm(pdu/*, pdu*//*);

     case H225_RasMessage::e_disengageReject :
       return OnReceiveDisengageReject(pdu/*, pdu*//*);

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

     case H225_RasMessage::e_resourcesAvailableConfirm :
       return OnReceiveResourcesAvailableConfirm(pdu/*, pdu*//*);

     case H225_RasMessage::e_infoRequestAck :
       return OnReceiveInfoRequestAck(pdu, pdu);

     case H225_RasMessage::e_infoRequestNak :
    return OnReceiveInfoRequestNak(pdu, pdu);

 #ifdef H323_H248
     case H225_RasMessage::e_serviceControlIndication :
       if (SendCachedResponse(pdu))
         return FALSE;
       OnReceiveServiceControlIndication(pdu, pdu);
       break;

     case H225_RasMessage::e_serviceControlResponse :
       return OnReceiveServiceControlResponse(pdu, pdu);
 #endif

     default :
       OnReceiveUnknown(pdu);
   }

   return FALSE;
 }*/