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
    QTime time = QTime::currentTime();
    QString currentTime = time.toString("hh:mm:ss.zzz");//(Qt::LocalDate);

    QString str = "[ " + currentTime + " ]  " + log;
    logs.append(str);
    emit updateLogs(str);
    //QTextStream out(logFile);
    //out<<str;
    //out<<"\n";
}

LogManager::LogManager()
{
    //logFile = new QFile("logFile.txt");
    //logFile->open(QIODevice::Append | QIODevice::Text);
}


void LogManager::clearLogs()
{
    logs.clear();
}
