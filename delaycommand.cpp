#include "delaycommand.h"

DelayCommand::DelayCommand(int state, int seconds)
    : Command(state)
{
    delay = seconds;
    //LogManager &log = LogManager::Instance();
    //log.PushLog(QString::number(delay));
}
DelayCommand::~DelayCommand()
{
}

H323GatekeeperRequest::Response DelayCommand::execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info);//*/H323GatekeeperRequest *grqInfo)
{
    //LogManager &log = LogManager::Instance();
    //log.PushLog(QString::number(delay));
    QTime t;
    t.start();
    while(t.elapsed() < delay)
    {}
    return H323GatekeeperRequest::Confirm;
}
