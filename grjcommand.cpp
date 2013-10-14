#include "grjcommand.h"

H323GatekeeperRequest::Response GRJCommand::execute(H323GatekeeperListener *listener, /*H323GatekeeperGRQ &info)//*/H323GatekeeperRequest *grqInfo)
{
    /*if (info.grq.m_protocolIdentifier.GetSize() != 6 || info.grq.m_protocolIdentifier[5] < 2) {
     info.SetRejectReason(H225_GatekeeperRejectReason::e_invalidRevision);
     PTRACE(2, "RAS\tGRQ rejected, version 1 not supported");
     return H323GatekeeperRequest::Reject;
   }

   if (!info.CheckGatekeeperIdentifier())
     return H323GatekeeperRequest::Reject;*/
    return H323GatekeeperRequest::Reject;
}

GRJCommand::GRJCommand(int state)
    :Command(state)
{
}

GRJCommand::~GRJCommand()
{
}

/*PString GRJCommand::GetName()
{
    return "GRJ";
}*/



