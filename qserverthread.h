#ifndef QSERVERTHREAD_H
#define QSERVERTHREAD_H

//#include "killerthread.h"
#include <QThread>
#include "gatekeeperserver.h"
#include "endpoint.h"
//#include <h323.h>
#include "actionmanager.h"
#include "logmanager.h"

//void makeServer();

class QServerThread : public QThread
{
    Q_OBJECT
    void run();// Q_DECL_OVERRIDE;
    bool flag;
    GatekeeperServer *server;
public:
    explicit QServerThread(QObject *parent = 0);
    void StartThread(QFile*);
    
signals:
    void update(QString);
public slots:
    void end();

};

#endif // QSERVERTHREAD_H
