#include "gatekeeperserver.h"

void GatekeeperServer::Configure()
{
    mGKPorts.push_back(H225_RAS::DefaultRasMulticastPort);
    mGKPorts.push_back(H225_RAS::DefaultRasUdpPort);

    PIPSocket::InterfaceTable IT;
    PIPSocket::GetInterfaceTable(IT);
    std::cout<<"ITSize "<<IT.GetSize()<<std::endl;
    for(int i = 0; i < IT.GetSize(); i++)
    {
        mGKAddrs.push_back(IT[i].GetAddress());
    }
}

void GatekeeperServer::Terminate()
{
    mGKAddrs.clear();
    mGKPorts.clear();

    //delete list of listeners!
}

void GatekeeperServer::GetTransportsByReference(H323EndPoint *Endpoint, vector<H323TransportUDP *> &Transport)
{
    Configure();
    for(vector<PIPSocket::Address>::iterator i = mGKAddrs.begin(); i != mGKAddrs.end(); i++)
    {
        for(vector<WORD>::iterator j = mGKPorts.begin(); j != mGKPorts.end(); j++)
        {
            Transport.push_back(new H323TransportUDP(*Endpoint, *i, *j));
        }
    }
}

void GatekeeperServer::RemoveTransports(vector<H323TransportUDP *> &Transports)
{
    for(unsigned i = 0; i < Transports.size(); i++)
    {
        delete Transports[i];
    }
    Transports.clear();
}

GatekeeperServer::GatekeeperServer(H323EndPoint &endpoint)
    : H323GatekeeperServer(endpoint)
{
    std::cout<<"Create a gatekeeper!"<<std::endl;    

    //this->SetGatekeeperIdentifier("Gatekeeper", 1);
    //this->SetTimeToLive(1200);
    //this->SetAvailableBandwidth(32);
    //this->SetInfoResponseRate(10);

    //endpoint.SetLocalUserName("Luba");

    vector<H323TransportUDP *> transports;
    GetTransportsByReference(&endpoint, transports);
    std::cout<<transports.size()<<std::endl;
    for(vector<H323TransportUDP *>::iterator i = transports.begin(); i != transports.end(); i++)
    {
        listeners.push_back(new GatekeeperListener(endpoint, *this, this->GetGatekeeperIdentifier(), *i));
    }

    for(list<GatekeeperListener*>::iterator i = listeners.begin(); i != listeners.end(); i++)
    {
        if(AddListener(*i))
            std::cout<<"Listener "<<(*i)->GetInterfaceAddresses()<<" was added!"<<std::endl;
    }
}


GatekeeperServer::~GatekeeperServer(void)
{
    Terminate();    
}

H323GatekeeperRequest::Response GatekeeperServer::OnDiscovery(H323GatekeeperGRQ &info)
{
    PTRACE_BLOCK("H323GatekeeperServer::OnDiscovery");

    std::cout<<"onDiscovery!"<<std::endl;
    H235Authenticators authenticators = ownerEndPoint.CreateAuthenticators();
    for (PINDEX auth = 0; auth < authenticators.GetSize(); auth++) {
     for (PINDEX cap = 0; cap < info.grq.m_authenticationCapability.GetSize(); cap++) {
           for (PINDEX alg = 0; alg < info.grq.m_algorithmOIDs.GetSize(); alg++) {
               //для телефона закомментить иф
            if (authenticators[auth].IsCapability(info.grq.m_authenticationCapability[cap],
                                                  info.grq.m_algorithmOIDs[alg])) {

             PTRACE(3, "RAS\tGRQ accepted on " << H323TransportAddress(info.gcf.m_rasAddress)
                   << " using authenticator " << authenticators[auth]);

                std::cout<<"RAS\tGRQ accepted on " << H323TransportAddress(info.gcf.m_rasAddress)
                   << " using authenticator " << authenticators[auth]<<std::endl;

             info.gcf.IncludeOptionalField(H225_GatekeeperConfirm::e_authenticationMode);
             info.gcf.m_authenticationMode = info.grq.m_authenticationCapability[cap];

              info.gcf.IncludeOptionalField(H225_GatekeeperConfirm::e_algorithmOID);
              info.gcf.m_algorithmOID = info.grq.m_algorithmOIDs[alg];

              return H323GatekeeperRequest::Confirm;
         }
       }

     }
   }


    /*info.gcf.IncludeOptionalField(H225_GatekeeperConfirm::e_tokens);

    info.gcf.m_tokens.SetSize(1);
    info.gcf.m_tokens[0].IncludeOptionalField(H235_ClearToken::e_generalID);
    info.gcf.m_tokens[0].IncludeOptionalField(H235_ClearToken::e_random);
    info.gcf.m_tokens[0].IncludeOptionalField(H235_ClearToken::e_timeStamp);
    info.gcf.m_tokens[0].m_generalID.SetValue("SERVERLuba");
    info.gcf.m_tokens[0].m_random.SetValue(42);*/

    return H323GatekeeperRequest::Confirm;
}

 H323GatekeeperRequest::Response GatekeeperServer::OnRegistration(H323GatekeeperRRQ & info)
 {
   PTRACE_BLOCK("H323GatekeeperServer::OnRegistration");
   std::cout<<"onRegistration!"<<std::endl;
   PINDEX i;

   // Initialise reply with default stuff
   info.rcf.IncludeOptionalField(H225_RegistrationConfirm::e_preGrantedARQ);
   info.rcf.m_preGrantedARQ.m_answerCall = answerCallPreGrantedARQ;
   info.rcf.m_preGrantedARQ.m_useGKCallSignalAddressToAnswer = answerCallPreGrantedARQ && isGatekeeperRouted;
   info.rcf.m_preGrantedARQ.m_makeCall = makeCallPreGrantedARQ;
   info.rcf.m_preGrantedARQ.m_useGKCallSignalAddressToMakeCall = makeCallPreGrantedARQ && isGatekeeperRouted;
   info.rcf.m_willRespondToIRR = TRUE;

   if (defaultInfoResponseRate > 0 && info.rrq.m_protocolIdentifier[5] > 2) {
     info.rcf.m_preGrantedARQ.IncludeOptionalField(H225_RegistrationConfirm_preGrantedARQ::e_irrFrequencyInCall);
     info.rcf.m_preGrantedARQ.m_irrFrequencyInCall = defaultInfoResponseRate;
   }

   if (info.rrq.m_keepAlive) {
     if (info.endpoint != NULL)
     {
         std::cout<<"return info.endpoint->OnRegistration(info)"<<std::endl;
       return info.endpoint->OnRegistration(info);
     }

     info.SetRejectReason(H225_RegistrationRejectReason::e_fullRegistrationRequired);
     PTRACE(2, "RAS\tRRQ keep alive rejected, not registered");
     std::cout<<"Reject"<<std::endl;
     return H323GatekeeperRequest::Reject;
   }

   for (i = 0; i < info.rrq.m_callSignalAddress.GetSize(); i++) {
     PSafePtr<H323RegisteredEndPoint> ep2 = FindEndPointBySignalAddress(info.rrq.m_callSignalAddress[i]);
     if (ep2 != NULL && ep2 != info.endpoint) {
       if (overwriteOnSameSignalAddress) {
         PTRACE(2, "RAS\tOverwriting existing endpoint " << *ep2);
         RemoveEndPoint(ep2);
       }
       else {
         info.SetRejectReason(H225_RegistrationRejectReason::e_invalidCallSignalAddress);
         PTRACE(2, "RAS\tRRQ rejected, duplicate callSignalAddress");
         std::cout<<"Reject"<<std::endl;
         return H323GatekeeperRequest::Reject;
       }
     }
   }

   if (info.rrq.HasOptionalField(H225_RegistrationRequest::e_terminalAlias) && !AllowDuplicateAlias(info.rrq.m_terminalAlias)) {
     H225_ArrayOf_AliasAddress duplicateAliases;
     for (i = 0; i < info.rrq.m_terminalAlias.GetSize(); i++) {
       PSafePtr<H323RegisteredEndPoint> ep2 = FindEndPointByAliasAddress(info.rrq.m_terminalAlias[i]);
       if (ep2 != NULL && ep2 != info.endpoint) {
         PINDEX sz = duplicateAliases.GetSize();
         duplicateAliases.SetSize(sz+1);
               duplicateAliases[sz] = info.rrq.m_terminalAlias[i];
       }
     }
     if (duplicateAliases.GetSize() > 0) {
       info.SetRejectReason(H225_RegistrationRejectReason::e_duplicateAlias);
       H225_ArrayOf_AliasAddress & reasonAliases = info.rrj.m_rejectReason;
       reasonAliases = duplicateAliases;
       PTRACE(2, "RAS\tRRQ rejected, duplicate alias");
       std::cout<<"Reject"<<std::endl;
       return H323GatekeeperRequest::Reject;
     }
   }

   // Check if the endpoint is trying to register a prefix that can be resolved to another endpoint
   const H225_EndpointType & terminalType = info.rrq.m_terminalType;
   if (terminalType.HasOptionalField(H225_EndpointType::e_gateway) &&
       terminalType.m_gateway.HasOptionalField(H225_GatewayInfo::e_protocol)) {
     const H225_ArrayOf_SupportedProtocols & protocols = terminalType.m_gateway.m_protocol;

     for (i = 0; i < protocols.GetSize(); i++) {

       // Only voice prefixes are supported
       if (protocols[i].GetTag() == H225_SupportedProtocols::e_voice) {
             H225_VoiceCaps & voiceCaps = protocols[i];
               if (voiceCaps.HasOptionalField(H225_VoiceCaps::e_supportedPrefixes)) {
                 H225_ArrayOf_SupportedPrefix & prefixes = voiceCaps.m_supportedPrefixes;
                 for (PINDEX j = 0; j < prefixes.GetSize(); j++) {

                   // Reject if the prefix be matched to a registered alias or prefix
                   PSafePtr<H323RegisteredEndPoint> ep2 = FindEndPointByAliasAddress(prefixes[j].m_prefix);
                   if (ep2 != NULL && ep2 != info.endpoint && !canHaveDuplicatePrefix) {
                     info.SetRejectReason(H225_RegistrationRejectReason::e_duplicateAlias);
               H225_ArrayOf_AliasAddress & aliases = info.rrj.m_rejectReason;
               aliases.SetSize(1);
                     aliases[0] = prefixes[j].m_prefix;
                     PTRACE(2, "RAS\tRRQ rejected, duplicate prefix");
                     std::cout<<"Reject"<<std::endl;
                     return H323GatekeeperRequest::Reject;
             }
           }
               }
               break;  // If voice protocol is found, don't look any further
       }
     }
   }

    info.rcf.m_timeToLive = this->GetTimeToLive();
   // Are already registered and have just sent another heavy RRQ
   if (info.endpoint != NULL) {
     H323GatekeeperRequest::Response response = info.endpoint->OnRegistration(info);
     switch (response) {
       case H323GatekeeperRequest::Confirm :
         AddEndPoint(info.endpoint);
         break;
       case H323GatekeeperRequest::Reject :
         RemoveEndPoint(info.endpoint);
         break;
       default :
         break;
     }
     std::cout<<"Response"<<std::endl;
     return response;
   }

   // Need to create a new endpoint object
   info.endpoint = CreateRegisteredEndPoint(info);
   if (info.endpoint == (H323RegisteredEndPoint *)NULL) {
     PTRACE(1, "RAS\tRRQ rejected, CreateRegisteredEndPoint() returned NULL");
     std::cout<<"Reject"<<std::endl;
     return H323GatekeeperRequest::Reject;
   }

   H323GatekeeperRequest::Response response = info.endpoint->OnRegistration(info);
   if (response != H323GatekeeperRequest::Confirm) {
    info.endpoint = (H323RegisteredEndPoint *)NULL;
     delete info.endpoint;
     std::cout<<"Responce"<<std::endl;
    return response;
   }

   // Have successfully registered, save it
   AddEndPoint(info.endpoint);

   PTRACE(2, "RAS\tRRQ accepted: \"" << *info.endpoint << '"');
   std::cout<<"Confirm"<<std::endl;
   return H323GatekeeperRequest::Confirm;
 }

