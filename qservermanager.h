#ifndef QSERVERMANAGER_H
#define QSERVERMANAGER_H

#include <QObject>
#include <QVector>
#include "gatekeeperserver.h"
#include "statemachine.h"
#include "options.h"
#include "scenario.h"

class QServerManager : public QObject
{
    Q_OBJECT

    GatekeeperServer *mServer;
    H323EndPoint *mEndPoint;
    Scenario* mScenario;
    OptionManager::Options* mOptions;
    bool PrepareTestCase(const QString& scenarioName);
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
