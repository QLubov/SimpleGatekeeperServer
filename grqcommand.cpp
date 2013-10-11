#include "grqcommand.h"

H323GatekeeperRequest::Response GRQCommand::execute(H323GatekeeperListener *listener, H323GatekeeperRequest &info)
{
    std::cout<<" GRQCommand"<<std::endl;

    ActionManager &mng = ActionManager::Instance();

    if(mng.CheckState(2) || mng.CheckState(1))
        return mng.ExecuteCommand(listener, info);
    else
    {
        std::cout<<" Err in GRQCommand!"<<std::endl;
        //LogWindow & log = LogWindow::Instance();
        //log.update(QString(QString("Err in GRQCommand!")));
    }


    return H323GatekeeperRequest::Confirm;

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


