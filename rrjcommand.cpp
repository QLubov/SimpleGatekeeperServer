#include "rrjcommand.h"

RRJCommand::RRJCommand(int state)
    : Command(state)
{
}
RRJCommand::~RRJCommand()
{
}
H323GatekeeperRequest::Response RRJCommand::execute(H323GatekeeperListener *listener, H323GatekeeperRequest *rrqInfo)
{
    return H323GatekeeperRequest::Reject;
}
