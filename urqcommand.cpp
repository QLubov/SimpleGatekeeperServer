#include "urqcommand.h"

URQCommand::URQCommand(int state)
    : Command(state)
{
}

URQCommand::~URQCommand()
{
}

H323GatekeeperRequest::Response URQCommand::execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info);//*/H323GatekeeperRequest *urqInfo)
{
    std::cout<<" URQCommand"<<std::endl;

    ActionManager &mng = ActionManager::Instance();

    if(mng.CheckState(UCF) || mng.CheckState(URJ))
        return mng.ExecuteCommand(listener, urqInfo);
    else
    {
        LogManager &log = LogManager::Instance();
        log.PushLog(QString("Scenario is invalid"));
        std::cout<<" Err in URQCommand!"<<std::endl;
        return H323GatekeeperRequest::Reject;
    }

}
