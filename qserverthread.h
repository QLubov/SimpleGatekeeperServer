#ifndef QSERVERTHREAD_H
#define QSERVERTHREAD_H


#include <QThread>
#include "gatekeeperserver.h"
#include "endpoint.h"
//#include <h323.h>

void makeServer();

class QServerThread : public QThread
{
    Q_OBJECT
void run();// Q_DECL_OVERRIDE;
public:
    explicit QServerThread(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // QSERVERTHREAD_H
