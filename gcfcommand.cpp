#include "gcfcommand.h"

H323GatekeeperRequest::Response GCFCommand::execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info)//*/H323GatekeeperRequest *grqInfo)
{
    std::cout<<" GCFCommand"<<std::endl;

    // cannot use commented code because transport->remoteAddr is
    // not set on broadcast PDUs
     //     transport->SetUpTransportPDU(info.gcf.m_rasAddress, TRUE);

    H323GatekeeperGRQ *info = dynamic_cast<H323GatekeeperGRQ*>(grqInfo);
    if(info == 0)
    {
        //LogManager &log = LogManager::Instance();
        //log.PushLog(QString("Err in GatekeeperGRQ!"));
        return H323GatekeeperRequest::Reject;
    }

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
    //return H323GatekeeperRequest::Response::Confirm;
}

GCFCommand::GCFCommand(int state)
    :Command(state)
{
}

GCFCommand::~GCFCommand()
{
}

/*PString GCFCommand::GetName()
{
    return "GCF";
}*/
