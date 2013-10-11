#ifndef QSERVERTHREAD_H
#define QSERVERTHREAD_H


#include <QThread>
#include "gatekeeperserver.h"
#include "endpoint.h"
//#include <h323.h>
#include "actionmanager.h"
#include "logmanager.h"

void makeServer();

class QServerThread : public QThread
{
    Q_OBJECT
void run();// Q_DECL_OVERRIDE;
public:
    explicit QServerThread(QObject *parent = 0);
    void StartThread(QFile*);
    
signals:
    void update(QString);

};

#endif // QSERVERTHREAD_H
