#include "gcfcommand.h"

H323GatekeeperRequest::Response GCFCommand::execute(H323GatekeeperListener *listener, H323GatekeeperRequest *grqInfo)
{
    ActionManager &mng = ActionManager::Instance();
    std::cout<<" GCFCommand"<<std::endl;
    H323GatekeeperGRQ *info = dynamic_cast<H323GatekeeperGRQ*>(grqInfo);
    if(info == 0)
    {
        LogManager &log = LogManager::Instance();
        log.PushLog(QString("GRQ is invalid"));
        mng.deleteScenario();
        return H323GatekeeperRequest::Reject;
    }

    if (info->grq.m_protocolIdentifier.GetSize() != 6 || info->grq.m_protocolIdentifier[5] < 2) {
     info->SetRejectReason(H225_GatekeeperRejectReason::e_invalidRevision);     
     LogManager &log = LogManager::Instance();
     log.PushLog(QString("Err in GatekeeperGCF: GRQ rejected, version 1 not supported"));
     mng.deleteScenario();
     return H323GatekeeperRequest::Reject;
    }

   if (!info->CheckGatekeeperIdentifier())
   {
       LogManager &log = LogManager::Instance();
       log.PushLog(QString("Sending GCF failed"));
       mng.deleteScenario();
       return H323GatekeeperRequest::Reject;
   }

    // cannot use commented code because transport->remoteAddr is
    // not set on broadcast PDUs
     //     transport->SetUpTransportPDU(info.gcf.m_rasAddress, TRUE);



    {
      PIPSocket::Address localAddr, remoteAddr;
      WORD localPort;
      listener->GetTransport().GetLocalAddress().GetIpAndPort(localAddr, localPort);
      H323TransportAddress(info->grq.m_rasAddress).GetIpAddress(remoteAddr);
      listener->GetEndPoint().InternalTranslateTCPAddress(localAddr, remoteAddr);
      listener->GetEndPoint().TranslateTCPPort(localPort,remoteAddr);
      H323TransportAddress newAddr = H323TransportAddress(localAddr, localPort);

      H225_TransportAddress & pdu = info->gcf.m_rasAddress;
      newAddr.SetPDU(pdu);
    }

    return listener->GetGatekeeper().OnDiscovery(*info);

}

GCFCommand::GCFCommand(int state)
    :Command(state)
{
}

GCFCommand::~GCFCommand()
{
}

