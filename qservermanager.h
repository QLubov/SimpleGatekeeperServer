#ifndef QSERVERMANAGER_H
#define QSERVERMANAGER_H

#include <QObject>
#include <QVector>
#include "gatekeeperserver.h"
#include "statemachine.h"

class QServerManager : public QObject
{
    Q_OBJECT

    GatekeeperServer *mServer;
    H323EndPoint *mEndPoint;
    void ConnectObjects(GatekeeperListener* listener);
public:
    explicit QServerManager(QObject *parent = 0);
    void InitServer(const QString& scenarioName);
public slots:
    void OnTerminate(bool success);
signals:
    void Finished(bool success);
};

#endif // QSERVERMANAGER_H
