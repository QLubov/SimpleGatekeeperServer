#include "logmanager.h"

LogManager* LogManager::instance = 0;

LogManager& LogManager::Instance()
{
    if(!instance)
        instance = new LogManager();
    return *instance;
}

void LogManager::PushLog(QString &log)
{
    logs.append(log);
    emit updateLogs(log);
}

LogManager::LogManager()
{
}
void LogManager::clearLogs()
{
    logs.clear();
}
