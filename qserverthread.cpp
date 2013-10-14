#include "qserverthread.h"

/*void makeServer()
{
    LogManager &log = LogManager::Instance();
    log.PushLog(QString("in makeserver!"));
    /*H323EndPoint ep;
    H323GatekeeperServer *serv = new H323GatekeeperServer(ep);
    serv->SetGatekeeperIdentifier("LubaSERVER");
    PString iface, listenPort;
    iface = "127.0.0.1";//"93.120.171.32";//"192.168.135.49";
        //iface = "224.0.1.41";
    listenPort = "1719";
        //listenPort = H225_RAS::DefaultRasMulticastPort;

    PIPSocket::Address interfaceAddress(iface);
    WORD interfacePort = (WORD)listenPort.AsInteger();
    H323Transport *transport = new H323TransportUDP(ep, interfaceAddress, interfacePort, 1);

    H323GatekeeperListener *tr = new H323GatekeeperListener(ep, *serv, serv->GetGatekeeperIdentifier(), transport);

    if(serv->AddListener(tr))
        std::cout<<"Listener "<<tr->GetInterfaceAddresses()<<" was added!"<<std::endl;*/
   /* EndPoint ep;
    GatekeeperServer *gk = new GatekeeperServer(ep);
    //GatekeeperServer gk(ep);
    for (;;)
        {
           /* PCaselessString cmd;
            cin >> cmd;
            if (cmd == "X")
              break;*/

       /* }

}*/
QServerThread::QServerThread(QObject *parent) :
    QThread(parent)
{
    flag = true;
}

void QServerThread::run()
{

    //makeServer();
    H323EndPoint ep;
    server = new GatekeeperServer(ep);
    LogManager &log = LogManager::Instance();
    log.PushLog(QString("server run!"));
    while(flag)
    {
    }
    return;
}
void QServerThread::StartThread(QFile *file)
{
    ActionManager &mng = ActionManager::Instance();
    mng.ParseXML(file);
    //connect(&mng, SIGNAL(error()), this, SLOT(end()));
    LogManager &log = LogManager::Instance();
    connect(&log, SIGNAL(updateLogs(QString)), this, SIGNAL(update(QString)));
    //log.PushLog(QString("in StartThread!"));

    this->start();
}
void QServerThread::end()
{
    //exit(0);
    //deleteLater();
    LogManager &log = LogManager::Instance();
    log.PushLog(QString("server stop!"));
    log.clearLogs();
    delete server;
    flag = false;


    //deleteLater();
}
