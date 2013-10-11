#include "qserverthread.h"

void makeServer()
{
    H323EndPoint ep;
    H323GatekeeperServer *serv = new H323GatekeeperServer(ep);
    serv->SetGatekeeperIdentifier("LubaSERVER");
    PString iface, listenPort;
    iface = "192.168.135.49";
        //iface = "224.0.1.41";
    listenPort = "1719";
        //listenPort = H225_RAS::DefaultRasMulticastPort;

    PIPSocket::Address interfaceAddress(iface);
    WORD interfacePort = (WORD)listenPort.AsInteger();
    H323Transport *transport = new H323TransportUDP(ep, interfaceAddress, interfacePort, 1);

    H323GatekeeperListener *tr = new H323GatekeeperListener(ep, *serv, serv->GetGatekeeperIdentifier(), transport);

    if(serv->AddListener(tr))
        std::cout<<"Listener "<<tr->GetInterfaceAddresses()<<" was added!"<<std::endl;
    //EndPoint ep;
    //GatekeeperServer *gk = new GatekeeperServer(ep);
    for (;;)
        {
           /* PCaselessString cmd;
            cin >> cmd;
            if (cmd == "X")
              break;*/

        }
}
QServerThread::QServerThread(QObject *parent) :
    QThread(parent)
{
}

void QServerThread::run()
{
    makeServer();
}
