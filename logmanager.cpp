#include "logmanager.h"

LogManager& LogManager::Instance()
{    
    static LogManager instance;
    return instance;
}

void LogManager::PushLog(const QString &log)
{
    QTime time = QTime::currentTime();
    QString currentTime = time.toString("hh:mm:ss.zzz");

    QString str = "[ " + currentTime + " ]  " + log;
    logs.append(str);
    emit updateLogs(str);    
}

LogManager::LogManager()
{
}


void LogManager::clearLogs()
{
    logs.clear();
}
