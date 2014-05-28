#include "action.h"
#include <QVector>
#include <QTime>
#include <QDomNode>
#include "logmanager.h"
#include "gatekeeperlistener.h"

Action::Action()
{
}

Action::~Action()
{
}

bool SendGCF::OnLoad(QDomNode &node)
{
    return true;
}

void SendGCF::execute(GatekeeperListener *listener, const H323RasPDU &pdu)
{
    LOG("<--GRQ");
    listener->OnReceiveGatekeeperRequest(pdu, pdu);
    LOG("-->GCF");
}

QString SendGCF::GetName()
{
    return "SendGCF";
}

bool SendRCF::OnLoad(QDomNode &node)
{
    return true;
}

void SendRCF::execute(GatekeeperListener *listener, const H323RasPDU &pdu)
{
    LOG("<--RRQ");
    listener->OnReceiveRegistrationRequest(pdu, pdu);
    LOG("-->RCF");
}

QString SendRCF::GetName()
{
    return "SendRCF";
}

bool SendUCF::OnLoad(QDomNode &node)
{
    return true;
}

void SendUCF::execute(GatekeeperListener *listener, const H323RasPDU &pdu)
{
    LOG("<--URQ");
    listener->OnReceiveUnregistrationRequest(pdu, pdu);
    LOG("-->UCF");
}

QString SendUCF::GetName()
{
    return "SendUCF";
}

bool SendACF::OnLoad(QDomNode &node)
{
    return true;
}

void SendACF::execute(GatekeeperListener *listener, const H323RasPDU &pdu)
{
    LOG("<--ARQ");
    listener->OnReceiveAdmissionRequest(pdu, pdu);
    LOG("-->ACF");
}

QString SendACF::GetName()
{
    return "SendACF";
}

bool Delay::OnLoad(QDomNode &node)
{
    mMSec = node.firstChild().nodeValue().toInt();
    return true;
}

void Delay::execute(GatekeeperListener *listener, const H323RasPDU &pdu)
{
    QTime time;
    time.start();
    LOG("Delay " + QString::number(mMSec) + " msec");
    while(time.elapsed() < mMSec);
}

QString Delay::GetName()
{
    return "Delay " + QString::number(mMSec) + " msec";
}


bool EndAction::OnLoad(QDomNode &node)
{
    return true;
}

void EndAction::execute(GatekeeperListener *listener, const H323RasPDU &pdu)
{
    listener->EmitFinish(true);
}

QString EndAction::GetName()
{
    return "";
}
