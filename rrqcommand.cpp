#include "rrqcommand.h"

RRQCommand::RRQCommand(int state)
    :Command(state)
{
}

RRQCommand::~RRQCommand()
{
}

H323GatekeeperRequest::Response RRQCommand::execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info)//*/H323GatekeeperRequest *rrqInfo)
{
    std::cout<<" RRQCommand"<<std::endl;

    ActionManager &mng = ActionManager::Instance();

    if(mng.CheckState(RCF) || mng.CheckState(RRJ))
        return mng.ExecuteCommand(listener, rrqInfo);
    else
    {
        LogManager &log = LogManager::Instance();
        log.PushLog(QString(" Err in RRQCommand!"));
        std::cout<<" Err in RRQCommand!"<<std::endl;
        //stop gatekeeperserver
        //LogWindow & log = LogWindow::Instance();
        //log.update(QString(QString("Err in GRQCommand!")));
    }


    return H323GatekeeperRequest::Confirm;//exit

}
