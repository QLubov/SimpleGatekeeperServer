#include "grqcommand.h"

H323GatekeeperRequest::Response GRQCommand::execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info)//*/H323GatekeeperRequest *grqInfo)
{
    std::cout<<" GRQCommand"<<std::endl;

    ActionManager &mng = ActionManager::Instance();

    if(mng.CheckState(GCF) || mng.CheckState(GRJ))
        return mng.ExecuteCommand(listener, grqInfo);
    else
    {
        std::cout<<" Err in GRQCommand (scenario)!"<<std::endl;
        LogManager &log = LogManager::Instance();
        log.PushLog(QString("Err in GRQCommand!"));
        return H323GatekeeperRequest::Reject;
        //KillerThread &killer = KillerThread::Instance();
        //killer.Kill();
        //stop gatekeeperserver
        //LogWindow & log = LogWindow::Instance();
        //log.update(QString(QString("Err in GRQCommand!")));
    }


    //exit

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


