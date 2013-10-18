#include "grqcommand.h"

H323GatekeeperRequest::Response GRQCommand::execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info)//*/H323GatekeeperRequest *grqInfo)
{
    std::cout<<" GRQCommand"<<std::endl;

    ActionManager &mng = ActionManager::Instance();
    if(mng.CheckState(delay))
        mng.ExecuteCommand(listener, grqInfo);
    if(mng.CheckState(GCF) || mng.CheckState(GRJ))
        return mng.ExecuteCommand(listener, grqInfo);
    else
    {
        std::cout<<" Err in GRQCommand (scenario)!"<<std::endl;
        LogManager &log = LogManager::Instance();
        log.PushLog(QString("Scenario is invalid"));
        return H323GatekeeperRequest::Reject;        
    }   
}

GRQCommand::GRQCommand(int state)
    :Command(state)
{
}

GRQCommand::~GRQCommand()
{
}

