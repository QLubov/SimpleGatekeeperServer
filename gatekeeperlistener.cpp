#include "gatekeeperlistener.h"

GatekeeperListener::GatekeeperListener(H323EndPoint &endpoint, H323GatekeeperServer &server, const PString &gatekeeperIdentifier, H323Transport *transport)
: H323GatekeeperListener(endpoint, server, gatekeeperIdentifier, transport)
{    
    flag = false;
}

GatekeeperListener::~GatekeeperListener(void)
{
    StopChannel();
}
H323GatekeeperRequest::Response GatekeeperListener::OnDiscovery (H323GatekeeperGRQ & info)
{
    std::cout<<"onDiscovery in listener!"<<std::endl;
    LogManager &log = LogManager::Instance();
    log.PushLog(QString("Establish connection with " + info.GetReplyAddress().GetHostName()));

    ActionManager &mng = ActionManager::Instance();
    if(mng.CheckState(GRQ))
        return mng.ExecuteCommand(this, &info);
    else
    {
        std::cout<<"Err in onDiscovery!"<<std::endl;

        log.PushLog(QString("Error: Received GRQ instead " + mng.GetCommandName()));

        mng.deleteScenario();//the commands queue should be erased for exiting
        //return H323GatekeeperRequest::Reject;
    }


}

 H323GatekeeperRequest::Response GatekeeperListener::OnRegistration(H323GatekeeperRRQ & info)
 {
    std::cout<<"H323GatekeeperListener::OnRegistration"<<std::endl;    

    ActionManager &mng = ActionManager::Instance();
    if(mng.CheckState(RRQ))
    {        
        flag = true;
        return mng.ExecuteCommand(this, &info);
    }
    else
    {
        if(!flag)
        {
            std::cout<<"Err in onRegistration!"<<std::endl;
            LogManager &log = LogManager::Instance();
            log.PushLog(QString("Error: Received RRQ instead " + mng.GetCommandName()));
            mng.deleteScenario();
            //return H323GatekeeperRequest::Reject;
        }
        else
        {            
            return OnRegistrationInfo(info);//ping
        }        
    }
}

 H323GatekeeperRequest::Response GatekeeperListener::OnUnregistration(H323GatekeeperURQ & info)
  {       
    std::cout<<"H323GatekeeperListener::OnUnregistration"<<std::endl;

    ActionManager &mng = ActionManager::Instance();
    if(mng.CheckState(URQ))
        return mng.ExecuteCommand(this, &info);
    else
    {
        std::cout<<"Err in onUnregistration!"<<std::endl;
        LogManager &log = LogManager::Instance();
        log.PushLog(QString("Error: Received URQ instead " + mng.GetCommandName()));
        mng.deleteScenario();
        //return H323GatekeeperRequest::Reject;
    }    
  }


H323GatekeeperRequest::Response GatekeeperListener::OnRegistrationInfo(H323GatekeeperRRQ & info)
{
    std::cout<<" OnRegistrationInfo!"<<std::endl;
    H323GatekeeperRequest::Response response = gatekeeper.OnRegistration(info);
    if (response != H323GatekeeperRequest::Confirm)
    {
        std::cout<<" Err in RRQCommand!"<<std::endl;
        return H323GatekeeperRequest::Reject;

    }

    if (!info.rrq.m_keepAlive) {
      PSafePtr<H323RegisteredEndPoint> lock(info.endpoint, PSafeReadWrite);
      H235Authenticators authenticators = info.endpoint->GetAuthenticators();
      for (PINDEX i = 0; i < authenticators.GetSize(); i++) {
        H235Authenticator & authenticator = authenticators[i];
        if (authenticator.UseGkAndEpIdentifiers()) {
          authenticator.SetRemoteId(info.endpoint->GetIdentifier());
          authenticator.SetLocalId(GetIdentifier());
        }
      }
    }
  std::cout<<"H323GatekeeperListener::OnRegistration confirm!"<<std::endl;
    return H323GatekeeperRequest::Confirm;
}

