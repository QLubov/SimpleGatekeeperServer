#include "delaycommand.h"

DelayCommand::DelayCommand(int state, int seconds)
    : Command(state)
{
    delay = seconds;
}
DelayCommand::~DelayCommand()
{
}

H323GatekeeperRequest::Response DelayCommand::execute(H323GatekeeperListener *listener, H323GatekeeperRequest *grqInfo)
{

    QTime t;
    t.start();
    while(t.elapsed() < delay)
    {}
    return H323GatekeeperRequest::Confirm;
}
