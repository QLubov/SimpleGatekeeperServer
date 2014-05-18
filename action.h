#ifndef ACTION_H
#define ACTION_H
#include <QString.h>
//#include <QXmlStreamReader>

class QDomNode;
class GatekeeperListener;
class H323RasPDU;

class Action
{
public:
    Action();
    virtual ~Action();
    virtual bool OnLoad(QDomNode& node) = 0;
    virtual void execute(GatekeeperListener* listener, const H323RasPDU& pdu) = 0;
    virtual QString GetName() = 0;
};

class SendGCF : public Action
{
public:
    SendGCF(){}
    virtual ~SendGCF(){}
    virtual bool OnLoad(QDomNode& node);
    virtual void execute(GatekeeperListener* listener, const H323RasPDU& pdu);
    virtual QString GetName();
};

class SendRCF : public Action
{
public:
    SendRCF(){}
    virtual ~SendRCF(){}
    virtual bool OnLoad(QDomNode& node);
    virtual void execute(GatekeeperListener* listener, const H323RasPDU& pdu);
    virtual QString GetName();
};

class SendUCF : public Action
{
public:
    SendUCF(){}
    virtual ~SendUCF(){}
    virtual bool OnLoad(QDomNode& node);
    virtual void execute(GatekeeperListener* listener, const H323RasPDU& pdu);
    virtual QString GetName();
};

class SendACF : public Action
{
public:
    SendACF(){}
    virtual ~SendACF(){}
    virtual bool OnLoad(QDomNode& node);
    virtual void execute(GatekeeperListener* listener, const H323RasPDU& pdu);
    virtual QString GetName();
};

class Delay : public Action
{
    int mMSec;
public:
    Delay(){}
    virtual ~Delay(){}
    virtual bool OnLoad(QDomNode& node);
    virtual void execute(GatekeeperListener* listener, const H323RasPDU& pdu);
    virtual QString GetName();
};

#endif // ACTION_H
