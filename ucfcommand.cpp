#include "ucfcommand.h"

UCFCommand::UCFCommand(int state)
    : Command(state)
{
}

UCFCommand::~UCFCommand()
{
}

H323GatekeeperRequest::Response UCFCommand::execute(H323GatekeeperListener *listener, H323GatekeeperRequest *urqInfo)
{
    ActionManager &mng = ActionManager::Instance();
    H323GatekeeperURQ *info = dynamic_cast<H323GatekeeperURQ*>(urqInfo);
    if(info == 0)
    {
        LogManager &log = LogManager::Instance();
        log.PushLog(QString("URQ is invalid"));
        mng.deleteScenario();
        return H323GatekeeperRequest::Reject;
    }
    info->endpoint = listener->GetGatekeeper().FindEndPointBySignalAddresses(info->urq.m_callSignalAddress);

    if (info->endpoint == NULL) {
        info->SetRejectReason(H225_UnregRejectReason::e_notCurrentlyRegistered);        

        LogManager &log = LogManager::Instance();
        log.PushLog(QString("URQ rejected, not registered"));
        std::cout<<" Err in UCFCommand!"<<std::endl;
        mng.deleteScenario();
        return H323GatekeeperRequest::Reject;
  }
    H323GatekeeperRequest::Response response = listener->GetGatekeeper().OnUnregistration(*info);
    if (response != H323GatekeeperRequest::Confirm)
    {
        LogManager &log = LogManager::Instance();
        log.PushLog(QString("Sending UCF failed"));
        std::cout<<" Err in UCFCommand!"<<std::endl;
        mng.deleteScenario();
        return H323GatekeeperRequest::Reject;        
    }
    else
        return response;
}
