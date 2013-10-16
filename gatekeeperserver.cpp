#include "gatekeeperserver.h"


GatekeeperServer::GatekeeperServer(H323EndPoint &endpoint)
    : H323GatekeeperServer(endpoint)
{
    std::cout<<"Create a gatekeeper!"<<std::endl;
    //LogWindow& log = LogWindow::Instance();
    //log.ClearLogs();
    //log.show();
    //log.update(QString("Create a gatekeeper"));

    this->SetGatekeeperIdentifier("LubaServer", 1);
    this->SetTimeToLive(600);
    //this->SetAvailableBandwidth(32);
    //this->SetInfoResponseRate(10);

    std::cout<<endpoint.IsGatekeeper()<<std::endl;
    std::cout<<endpoint.FeatureSetDisabled()<<std::endl;
    std::cout<<endpoint.GetFeatureSet()<<std::endl;
    //endpoint.SetGkAccessTokenOID("itu-t.0");
    //endpoint.SetCapability(0, 0, new H323_G711Capability(H323_G711Capability::muLaw));
    //endpoint.SetCapability(0, 0, new H323_G711Capability(H323_G711Capability::ALaw));
    endpoint.SetLocalUserName("Luba");
    //endpoint.LoadBaseFeatureSet();
    //endpoint.SetQ931Display(true);

    //H323TransportAddress addr1("#ip$192.168.135.49:1719#");
    //H323TransportAddress addr2("#ip$127.0.0.1:1720#");
    PString iface, iface1, listenPort, listenPort1;//, listenPort2, listenPort3;
    iface = "192.168.135.49";
    iface1 = "127.0.0.1";
    listenPort = H225_RAS::DefaultRasUdpPort;//"1719";
    listenPort1 = H225_RAS::DefaultRasMulticastPort;
    //listenPort2 = "1720";
    //listenPort3 = "1721";

    PIPSocket::Address interfaceAddress(iface);
    WORD interfacePort = (WORD)listenPort.AsInteger();

    WORD interfacePort1 = (WORD)listenPort1.AsInteger();

    //WORD interfacePort2 = (WORD)listenPort2.AsInteger();

    //WORD interfacePort3 = (WORD)listenPort3.AsInteger();

    PIPSocket::Address interfaceAddress1(iface1);


    //WORD interfacePort3 = (WORD)listenPort.AsInteger();

    H323Transport *transport = new H323TransportUDP(endpoint, interfaceAddress, interfacePort, 1);
    H323Transport *transport1 = new H323TransportUDP(endpoint, interfaceAddress, interfacePort1, 1);
    //H323Transport *transport2 = new H323TransportUDP(endpoint, interfaceAddress, interfacePort2, 1);
    H323Transport *transport3 = new H323TransportUDP(endpoint, interfaceAddress1, interfacePort, 1);
    H323Transport *transport4 = new H323TransportUDP(endpoint, interfaceAddress1, interfacePort1, 1);
    //H323Transport *transport5 = new H323TransportUDP(endpoint, interfaceAddress1, interfacePort2, 1);

    //H323Transport *transport6 = new H323TransportUDP(endpoint, interfaceAddress, interfacePort3, 1);
    //H323Transport *transport7 = new H323TransportUDP(endpoint, interfaceAddress1, interfacePort3, 1);


    H323GatekeeperServer *server = this;//new H323GatekeeperServer(endpoint);
    //H323GatekeeperListener *tr = new SimpleGatekeeperListener(endpoint, *server, this->GetGatekeeperIdentifier(), transport);

    H323GatekeeperListener *tr = new GatekeeperListener(endpoint, *server, this->GetGatekeeperIdentifier(), transport);//new H323GatekeeperListener(endpoint, *server, this->GetGatekeeperIdentifier(), transport);
    H323GatekeeperListener *tr1 = new GatekeeperListener(endpoint, *server, this->GetGatekeeperIdentifier(), transport1);//H323GatekeeperListener(endpoint, *server, this->GetGatekeeperIdentifier(), transport1);
    //H323GatekeeperListener *tr2 = new H323GatekeeperListener(endpoint, *server, this->GetGatekeeperIdentifier(), transport2);
    H323GatekeeperListener *tr3 = new GatekeeperListener(endpoint, *server, this->GetGatekeeperIdentifier(), transport3);//new H323GatekeeperListener(endpoint, *server, this->GetGatekeeperIdentifier(), transport3);
    H323GatekeeperListener *tr4 = new GatekeeperListener(endpoint, *server, this->GetGatekeeperIdentifier(), transport4);
    //H323GatekeeperListener *tr5 = new H323GatekeeperListener(endpoint, *server, this->GetGatekeeperIdentifier(), transport5);
    //H323GatekeeperListener *tr6 = new H323GatekeeperListener(endpoint, *server, this->GetGatekeeperIdentifier(), transport6);
    //H323GatekeeperListener *tr7 = new H323GatekeeperListener(endpoint, *server, this->GetGatekeeperIdentifier(), transport7);

    //tr->SetCheckResponseCryptoTokens(true);
    tr->SetIdentifier(this->GetGatekeeperIdentifier());

    if(this->AddListener(tr))
    {
        std::cout<<"Listener "<<tr->GetInterfaceAddresses()<<" was added!"<<std::endl;
        //log.update(QString("Listener was added"));
    }
    if(this->AddListener(tr1))
    {
        std::cout<<"Listener "<<tr1->GetInterfaceAddresses()<<" was added!"<<std::endl;
        //log.update(QString("Listener was added"));
    }
    /*if(this->AddListener(tr2))
    {
        std::cout<<"Listener "<<tr2->GetInterfaceAddresses()<<" was added!"<<std::endl;
    }*/
    if(this->AddListener(tr3))
    {
        std::cout<<"Listener "<<tr3->GetInterfaceAddresses()<<" was added!"<<std::endl;
    }
    if(this->AddListener(tr4))
    {
        std::cout<<"Listener "<<tr4->GetInterfaceAddresses()<<" was added!"<<std::endl;
    }
    /*if(this->AddListener(tr5))
    {
        std::cout<<"Listener "<<tr5->GetInterfaceAddresses()<<" was added!"<<std::endl;
    }
    if(this->AddListener(tr6))
    {
        std::cout<<"Listener "<<tr6->GetInterfaceAddresses()<<" was added!"<<std::endl;
    }
    if(this->AddListener(tr7))
    {
        std::cout<<"Listener "<<tr7->GetInterfaceAddresses()<<" was added!"<<std::endl;
    }*/

}


GatekeeperServer::~GatekeeperServer(void)
{
}

/*H323GatekeeperRequest::Response GatekeeperServer::OnDiscovery(H323GatekeeperGRQ &info)
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



              //std::cout<<"0"<<std::endl;
               return H323GatekeeperRequest::Confirm;
         }
       }

     }
   }
     //info.gcf.IncludeOptionalField(H225_GatekeeperConfirm::e);
    //для телефона раскомментить
    //info.gcf.IncludeOptionalField(H225_GatekeeperConfirm::e_authenticationMode);
    //info.gcf.m_authenticationMode = info.grq.m_authenticationCapability[0];

    /*info.gcf.IncludeOptionalField(H225_GatekeeperConfirm::e_tokens);

    info.gcf.m_tokens.SetSize(1);
    info.gcf.m_tokens[0].IncludeOptionalField(H235_ClearToken::e_generalID);
    info.gcf.m_tokens[0].IncludeOptionalField(H235_ClearToken::e_random);
    info.gcf.m_tokens[0].IncludeOptionalField(H235_ClearToken::e_timeStamp);
    info.gcf.m_tokens[0].m_generalID.SetValue("SERVERLuba");
    info.gcf.m_tokens[0].m_random.SetValue(42);




    //для телефона раскомментить
   /* info.gcf.IncludeOptionalField(H225_GatekeeperConfirm::e_featureSet);
    info.gcf.m_featureSet.m_replacementFeatureSet = true;
    info.gcf.m_featureSet.IncludeOptionalField(H225_FeatureSet::e_desiredFeatures);
    info.gcf.m_featureSet.IncludeOptionalField(H225_FeatureSet::e_supportedFeatures);


    //для телефона раскомментить

    /*info.gcf.m_featureSet.m_supportedFeatures.SetSize(2);

    //info.gcf.m_featureSet.m_supportedFeatures[0].m_id = info.grq.m_featureSet.m_supportedFeatures[0].m_id;
    //info.gcf.m_featureSet.m_supportedFeatures[1].m_id = info.grq.m_featureSet.m_supportedFeatures[1].m_id;


    info.gcf.m_featureSet.m_supportedFeatures[0].m_parameters.SetSize(12);
    info.gcf.m_featureSet.m_supportedFeatures[1].m_parameters.SetSize(2);
    info.gcf.m_featureSet.m_supportedFeatures[0].IncludeOptionalField(H225_GenericIdentifier::e_standard);
    info.gcf.m_featureSet.m_supportedFeatures[1].IncludeOptionalField(H225_GenericIdentifier::e_standard);
    //info.gcf.m_featureSet.m_supportedFeatures[0].m_id = info.grq.m_featureSet.m_supportedFeatures[0].m_id;

    //info.gcf.m_featureSet.m_supportedFeatures[1].m_parameters[0].IncludeOptionalField(H225_EnumeratedParameter::e_content);
    info.gcf.m_featureSet.m_supportedFeatures[1].m_parameters[0].IncludeOptionalField(H225_GenericData::e_parameters);
    //info.gcf.m_featureSet.m_supportedFeatures[1].m_parameters[0].IncludeOptionalField(H225_Content::e_number8);

    info.gcf.m_featureSet.m_supportedFeatures[1].m_parameters[0].m_content = H225_Content::e_number8;
    info.gcf.m_featureSet.m_supportedFeatures[1].m_parameters[1].IncludeOptionalField(H225_GenericData::e_parameters);
    //info.gcf.m_featureSet.m_supportedFeatures[1].m_parameters[1].IncludeOptionalField(H225_Content::e_number16);
    info.gcf.m_featureSet.m_supportedFeatures[1].m_parameters[1].m_content = H225_Content::e_number16;

    info.gcf.m_featureSet.m_supportedFeatures[1].m_parameters[0].m_id = info.grq.m_featureSet.m_supportedFeatures[1].m_id.e_standard;
    std::cout<<"m_id  "<<info.gcf.m_featureSet.m_supportedFeatures[1].m_parameters[0].m_id<<std::endl;




    info.gcf.m_featureSet.m_supportedFeatures[1].m_parameters[0].m_id = H225_GenericIdentifier::e_standard;



    info.gcf.m_featureSet.m_desiredFeatures.SetSize(3);

    info.gcf.m_featureSet.m_desiredFeatures[0].IncludeOptionalField(H225_GenericIdentifier::e_standard);
    info.gcf.m_featureSet.m_desiredFeatures[1].IncludeOptionalField(H225_GenericIdentifier::e_standard);
    //info.gcf.m_featureSet.m_desiredFeatures[0].m_id= info.grq.m_featureSet.m_supportedFeatures[0].m_id.e_standard;
    //info.gcf.m_featureSet.m_desiredFeatures[1].m_id = info.grq.m_featureSet.m_supportedFeatures[1].m_id.e_standard;
    //info.gcf.m_featureSet.m_desiredFeatures[2].m_id = ownerEndPoint.GetFeatureSet();


    //info.gcf.m_featureSet.SetSize(2);
    /*info.gcf.m_featureSet.m_supportedFeatures = info.grq.m_featureSet.m_supportedFeatures;
    //info.gcf.m_featureSet.m_supportedFeatures[0].IncludeOptionalField(H225_GenericIdentifier::e_standard);
    //info.gcf.m_featureSet.m_supportedFeatures[0].m_parameters[0].IncludeOptionalField(H225_Content::e_number16);
    //std::cout<<"sizeoFArray  "<<info.gcf.m_featureSet.m_supportedFeatures[0].m_parameters.GetSize()<<std::endl;
    //std::cout<<"blahblah  "<<info.gcf.m_featureSet.m_supportedFeatures[0].m_parameters[0].m_id<<std::endl;
    //info.gcf.m_featureSet.m_supportedFeatures[0].m_parameters[0].m_id = H225_GenericIdentifier::
    //info.gcf.m_featureSet.m_desiredFeatures[0].m_parameters.SetSize(12);
    //info.gcf.m_featureSet.m_desiredFeatures[0].m_parameters[0].IncludeOptionalField(H225_EnumeratedParameter::e_content);
    //info.gcf.m_featureSet.m_desiredFeatures[0].m_parameters[0].m_id = 0;
    info.gcf.m_featureSet.m_desiredFeatures = info.grq.m_featureSet.m_supportedFeatures;
             */

  /*  std::cout<<"return Confirm  "<<std::endl;*/
   /* return H323GatekeeperRequest::Confirm;
}*/

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

/*
  H323GatekeeperRequest::Response GatekeeperServer::OnAdmission(H323GatekeeperARQ & info)
 {
   PTRACE_BLOCK("H323GatekeeperServer::OnAdmission");
   std::cout<<"onAdmission"<<std::cout;
   OpalGloballyUniqueID id = info.arq.m_callIdentifier.m_guid;
   if (id == NULL) {
     PTRACE(2, "RAS\tNo call identifier provided in ARQ!");
     info.SetRejectReason(H225_AdmissionRejectReason::e_undefinedReason);
     return H323GatekeeperRequest::Reject;
   }

   H323GatekeeperRequest::Response response;

   PSafePtr<H323GatekeeperCall> oldCall = FindCall(id, info.arq.m_answerCall);
   if (oldCall != NULL)
     response = oldCall->OnAdmission(info);
   else {
     // If on restarted in thread, then don't create new call, should already
     // have had one created on the last pass through.
     if (!info.IsFastResponseRequired() && info.CanSendRIP()) {
       PTRACE(2, "RAS\tCall object disappeared after starting slow PDU handler thread!");
       info.SetRejectReason(H225_AdmissionRejectReason::e_undefinedReason);
       return H323GatekeeperRequest::Reject;
     }

     H323GatekeeperCall * newCall = CreateCall(id,
                             info.arq.m_answerCall ? H323GatekeeperCall::AnsweringCall
                                                   : H323GatekeeperCall::OriginatingCall);
     PTRACE(3, "RAS\tCall created: " << *newCall);

     response = newCall->OnAdmission(info);

     if (response != H323GatekeeperRequest::Reject) {
       mutex.Wait();

       info.endpoint->AddCall(newCall);
       oldCall = activeCalls.Append(newCall);

       if (activeCalls.GetSize() > peakCalls)
         peakCalls = activeCalls.GetSize();
       totalCalls++;

       PTRACE(2, "RAS\tAdded new call (total=" << activeCalls.GetSize() << ") " << *newCall);
       mutex.Signal();

       AddCall(oldCall);
     }
   }

 #ifdef H323_H248
   switch (response) {
     case H323GatekeeperRequest::Confirm :
       if (oldCall->AddCallCreditServiceControl(info.acf.m_serviceControl))
         info.acf.IncludeOptionalField(H225_AdmissionConfirm::e_serviceControl);
       break;

     case H323GatekeeperRequest::Reject :
       if (oldCall != NULL && oldCall->AddCallCreditServiceControl(info.arj.m_serviceControl))
         info.arj.IncludeOptionalField(H225_AdmissionReject::e_serviceControl);
       break;

     default :
       break;
   }
 #endif

   return response;
 }
*/
 H323GatekeeperRequest::Response GatekeeperServer::OnRegistrationInfo(H323GatekeeperRRQ & info)
 {
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
 }
