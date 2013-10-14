#ifndef LOGMANAGER_H
#define LOGMANAGER_H
#include <QObject>

class LogManager : public QObject
{
    Q_OBJECT
public:
    static LogManager& Instance();
    void PushLog(QString&);
    ~LogManager(){}
    void clearLogs();
private:
    LogManager();
    LogManager (const LogManager&);
    LogManager& operator=(const LogManager&);
    static LogManager *instance;
    QList<QString> logs;
signals:
    void updateLogs(QString);
};

#endif // LOGMANAGER_H
