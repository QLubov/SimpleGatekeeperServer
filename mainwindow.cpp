#include "mainwindow.h"
#include "ui_mainwindow.h"
/*void run()
{
    /*H323EndPoint ep;
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
        std::cout<<"Listener "<<tr->GetInterfaceAddresses()<<" was added!"<<std::endl;*/
    /*EndPoint ep;
    GatekeeperServer *gk = new GatekeeperServer(ep);
    for (;;)
        {
           /* PCaselessString cmd;
            cin >> cmd;
            if (cmd == "X")
              break;*//*

        }
}*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //wnd = 0;
    //thread = new QServerThread(this);
}

MainWindow::~MainWindow()
{
    /*if(wnd)
        delete wnd;*/
    delete ui;    
}
/*void MainWindow::openLogWindow()
{
    wnd = new LogWindow(this);
    wnd->show();
}*/

void MainWindow::startScenario()
{
    QString name = QFileDialog::getOpenFileName(this, "Choose file", "d:/", "XML-files (*.xml)");
    if(!name.isEmpty())
    {
        ui->pushButton->setEnabled(false);
        QFile *file = new QFile(name);
        QServerThread *thread = new QServerThread(this);
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        thread->start();
    }
    //commands = xml.ReadFile(file);
    //int size = commands->size();

    //ActionManager &mng = ActionManager::Instance();
    //mng.ParseXML(file);
    //cout<<size<<endl;
    //if(mng.CountOfCommand())//size)
    //
    /*if(!wnd)
        openLogWindow();
    else
        wnd->ClearLogs();*/

    LogWindow& log = LogWindow::Instance(this);
    log.ClearLogs();
    log.show();
    log.update(QString("inMainWindow"));


    //run();
    //EndPoint ep;
    //GatekeeperServer *gk = new GatekeeperServer(ep);
    /*for(int i = 0; i < size; i++)
    {
        Command* cmd = commands->front();
        cmd->execute();
        commands->pop();
        QString mes = "Execute  " + QString::number(i);
        log.update(mes);
    }*/

   /* H323EndPoint ep;
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
    /*for (;;)
        {
           /* PCaselessString cmd;
            cin >> cmd;
            if (cmd == "X")
              break;*/

      //  }
}
void MainWindow::stopScenario()
{
    ui->pushButton->setEnabled(true);
    LogWindow& log = LogWindow::Instance(this);
    log.ClearLogs();
    //thread->quit();
    //delete thread;
}
