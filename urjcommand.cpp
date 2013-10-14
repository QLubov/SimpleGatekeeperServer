#include "urjcommand.h"

URJCommand::URJCommand(int state)
    : Command(state)
{
}

URJCommand::~URJCommand()
{
}

H323GatekeeperRequest::Response URJCommand::execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info);//*/H323GatekeeperRequest *urqInfo)
{
    return H323GatekeeperRequest::Reject;
}
