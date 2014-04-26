#ifndef QSERVERTHREAD_H
#define QSERVERTHREAD_H

#include <QThread>
#include "gatekeeperserver.h"
#include "endpoint.h"
#include "actionmanager.h"
#include "logmanager.h"

class QServerThread : public QThread
{
    Q_OBJECT
    void run();
    GatekeeperServer *mServer;
public:
    explicit QServerThread(const QString& scenarioName, QObject *parent = 0);

public slots:
    void StopServer();

};

#endif // QSERVERTHREAD_H
