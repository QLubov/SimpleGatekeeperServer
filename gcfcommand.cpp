#include "gcfcommand.h"

H323GatekeeperRequest::Response GCFCommand::execute(H323GatekeeperListener *listener, H323GatekeeperRequest &info)
{
    std::cout<<" GCFCommand"<<std::endl;

    // cannot use commented code because transport->remoteAddr is
    // not set on broadcast PDUs
     //     transport->SetUpTransportPDU(info.gcf.m_rasAddress, TRUE);
    /*{
      PIPSocket::Address localAddr, remoteAddr;
      WORD localPort;
      transport->GetLocalAddress().GetIpAndPort(localAddr, localPort);
      H323TransportAddress(info.grq.m_rasAddress).GetIpAddress(remoteAddr);
      endpoint.InternalTranslateTCPAddress(localAddr, remoteAddr);
      endpoint.TranslateTCPPort(localPort,remoteAddr);
      H323TransportAddress newAddr = H323TransportAddress(localAddr, localPort);

      H225_TransportAddress & pdu = info.gcf.m_rasAddress;
      newAddr.SetPDU(pdu);
    }*/

   // return gatekeeper.OnDiscovery(info);
    return H323GatekeeperRequest::Response::Confirm;
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