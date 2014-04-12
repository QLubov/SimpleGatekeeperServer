#include "rcfcommand.h"

RCFCommand::RCFCommand(int state)
    :Command(state)
{
}
RCFCommand::~RCFCommand()
{
}

H323GatekeeperRequest::Response RCFCommand::execute(H323GatekeeperListener *listener,/* H323GatekeeperGRQ &info)//*/H323GatekeeperRequest *rrqInfo)
{
    ActionManager &mng = ActionManager::Instance();
    H323GatekeeperRRQ *info = dynamic_cast<H323GatekeeperRRQ*>(rrqInfo);
    if(info == 0)
    {
        LogManager &log = LogManager::Instance();
        log.PushLog(QString("RRQ is invalid"));
        mng.deleteScenario();
        return H323GatekeeperRequest::Reject;
    }

     if (!info->CheckGatekeeperIdentifier())
     {
         LogManager &log = LogManager::Instance();
         log.PushLog(QString("Sending RCF failed"));
         std::cout<<" Err in RCFCommand!"<<std::endl;
         mng.deleteScenario();
         return H323GatekeeperRequest::Reject;         
     }

     if (info->rrq.m_protocolIdentifier.GetSize() != 6 || info->rrq.m_protocolIdentifier[5] < 2) {
         LogManager &log = LogManager::Instance();
         log.PushLog(QString("RRQ rejected, version 1 not supported"));
         std::cout<<" Err in RRQCommand!"<<std::endl;
       info->SetRejectReason(H225_RegistrationRejectReason::e_invalidRevision);
       mng.deleteScenario();
       return H323GatekeeperRequest::Reject;
     }

     H323GatekeeperRequest::Response response = listener->GetGatekeeper().OnRegistration(*info);
     if (response != H323GatekeeperRequest::Confirm)
     {
         LogManager &log = LogManager::Instance();
         log.PushLog(QString("Sending RCF failed"));
         std::cout<<" Err in RRQCommand!"<<std::endl;
         mng.deleteScenario();
         return H323GatekeeperRequest::Reject;        
     }

     // Adjust the authenticator remote ID to endpoint ID
     if (!info->rrq.m_keepAlive) {
       PSafePtr<H323RegisteredEndPoint> lock(info->endpoint, PSafeReadWrite);
       H235Authenticators authenticators = info->endpoint->GetAuthenticators();
       for (PINDEX i = 0; i < authenticators.GetSize(); i++) {
         H235Authenticator & authenticator = authenticators[i];
         if (authenticator.UseGkAndEpIdentifiers()) {
           authenticator.SetRemoteId(info->endpoint->GetIdentifier());
           authenticator.SetLocalId(listener->GetIdentifier());
         }
       }
     }
   std::cout<<"H323GatekeeperListener::OnRegistration confirm!"<<std::endl;
     return H323GatekeeperRequest::Confirm;    
}
