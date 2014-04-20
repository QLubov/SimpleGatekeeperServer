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
    bool needToClose;
    GatekeeperServer *server;
public:
    explicit QServerThread(const QString& scenarioName, QObject *parent = 0);

signals:
    void update(QString);
public slots:
    void end();

};

#endif // QSERVERTHREAD_H
