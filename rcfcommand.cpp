#include "rcfcommand.h"

RCFCommand::RCFCommand(int state)
    :Command(state)
{
}
RCFCommand::~RCFCommand()
{
}

H323GatekeeperRequest::Response RCFCommand::execute(H323GatekeeperListener *listener, H323GatekeeperGRQ &info)
{
    return H323GatekeeperRequest::Confirm;
}
