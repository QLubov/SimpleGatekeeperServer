#include "grqcommand.h"

H323GatekeeperRequest::Response GRQCommand::execute(H323GatekeeperListener *listener, H323GatekeeperGRQ &info)
{
    std::cout<<" GRQCommand"<<std::endl;

    ActionManager &mng = ActionManager::Instance();

    if(mng.CheckState(2) || mng.CheckState(1))
        return mng.ExecuteCommand(listener, info);
    else
    {
        std::cout<<" Err in GRQCommand!"<<std::endl;
        LogManager &log = LogManager::Instance();
        log.PushLog(QString("Err in GRQCommand!"));
        //LogWindow & log = LogWindow::Instance();
        //log.update(QString(QString("Err in GRQCommand!")));
    }


    return H323GatekeeperRequest::Confirm;//exit

}

GRQCommand::GRQCommand(int state)
    :Command(state)
{
}

GRQCommand::~GRQCommand()
{
}

/*PString GRQCommand::GetName()
{
    PString str("GRQ";)
    return str;
}*/


