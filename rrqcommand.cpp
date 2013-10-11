#include "rrqcommand.h"

RRQCommand::RRQCommand(int state)
    :Command(state)
{
}

RRQCommand::~RRQCommand()
{
}

H323GatekeeperRequest::Response RRQCommand::execute(H323GatekeeperListener *listener, H323GatekeeperGRQ &info)
{
    std::cout<<" RRQCommand"<<std::endl;

    ActionManager &mng = ActionManager::Instance();

    if(mng.CheckState(4))// || mng.CheckState(5))
        return mng.ExecuteCommand(listener, info);
    else
    {
        std::cout<<" Err in RRQCommand!"<<std::endl;
        //LogWindow & log = LogWindow::Instance();
        //log.update(QString(QString("Err in GRQCommand!")));
    }


    return H323GatekeeperRequest::Confirm;//exit

}
