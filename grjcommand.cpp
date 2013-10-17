#include "grjcommand.h"

H323GatekeeperRequest::Response GRJCommand::execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info)//*/H323GatekeeperRequest *grqInfo)
{    
    return H323GatekeeperRequest::Reject;
}

GRJCommand::GRJCommand(int state)
    :Command(state)
{
}

GRJCommand::~GRJCommand()
{
}


