#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QObject>
#include <QTime>
#include <QTextStream>
#include <QFile>

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
    QList<QString> logs;
signals:
    void updateLogs(QString);    
};

#endif // LOGMANAGER_H
