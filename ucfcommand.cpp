#include "ucfcommand.h"

UCFCommand::UCFCommand(int state)
    : Command(state)
{
}

UCFCommand::~UCFCommand()
{
}

H323GatekeeperRequest::Response UCFCommand::execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info);//*/H323GatekeeperRequest *urqInfo)
{
    H323GatekeeperURQ *info = dynamic_cast<H323GatekeeperURQ*>(urqInfo);
    if(info == 0)
    {
        LogManager &log = LogManager::Instance();
        log.PushLog(QString("Err in UCFCommand!"));
        return H323GatekeeperRequest::Reject;
    }
    info->endpoint = listener->GetGatekeeper().FindEndPointBySignalAddresses(info->urq.m_callSignalAddress);

    if (info->endpoint == NULL) {
        info->SetRejectReason(H225_UnregRejectReason::e_notCurrentlyRegistered);
        //PTRACE(2, "RAS\tURQ rejected, not registered");

        LogManager &log = LogManager::Instance();
        log.PushLog(QString(" Err in UCFCommand: URQ rejected, not registered"));
        std::cout<<" Err in UCFCommand!"<<std::endl;
        return H323GatekeeperRequest::Reject;
  }
    H323GatekeeperRequest::Response response = listener->GetGatekeeper().OnUnregistration(*info);
    if (response != H323GatekeeperRequest::Confirm)
    {
        LogManager &log = LogManager::Instance();
        log.PushLog(QString(" Err in UCFCommand!"));
        std::cout<<" Err in UCFCommand!"<<std::endl;
        return H323GatekeeperRequest::Reject;
        //exit
    }
    else
        return response;
}
