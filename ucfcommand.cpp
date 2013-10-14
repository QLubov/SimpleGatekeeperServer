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
        log.PushLog(QString("Err in RRQCommand!"));
        return H323GatekeeperRequest::Reject;
    }
    info->endpoint = listener->GetGatekeeper().FindEndPointBySignalAddresses(info->urq.m_callSignalAddress);

    if (info->endpoint == NULL) {
        //info.SetRejectReason(H225_UnregRejectReason::e_notCurrentlyRegistered);
        //PTRACE(2, "RAS\tURQ rejected, not registered");
        //return H323GatekeeperRequest::Reject;
        LogManager &log = LogManager::Instance();
        log.PushLog(QString(" Err in URQCommand!"));
        std::cout<<" Err in URQCommand!"<<std::endl;
  }
    H323GatekeeperRequest::Response response = listener->GetGatekeeper().OnUnregistration(*info);
    if (response != H323GatekeeperRequest::Confirm)
    {
        LogManager &log = LogManager::Instance();
        log.PushLog(QString(" Err in URQCommand!"));
        std::cout<<" Err in URQCommand!"<<std::endl;
        //exit
    }
    else
        return response;
}
