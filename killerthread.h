#ifndef KILLERTHREAD_H
#define KILLERTHREAD_H
#include <QObject>

class KillerThread : public QObject
{
    Q_OBJECT
public:
    static KillerThread& Instance();
    void Kill();
    ~KillerThread(){}
private:
    KillerThread();
    KillerThread (const KillerThread&);
    KillerThread& operator=(const KillerThread&);
    static KillerThread *instance;
signals:
    void exit();
};

#endif // KILLERTHREAD_H
