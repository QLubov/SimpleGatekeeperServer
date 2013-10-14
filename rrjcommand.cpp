#include "rrjcommand.h"

RRJCommand::RRJCommand(int state)
    : Command(state)
{
}
RRJCommand::~RRJCommand()
{
}
H323GatekeeperRequest::Response RRJCommand::execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info);//*/H323GatekeeperRequest *rrqInfo)//тут будет нужен ррку
{
    return H323GatekeeperRequest::Reject;
}
