#ifndef LOGWINDOW_H
#define LOGWINDOW_H
#pragma once
#include <QMainWindow>

namespace Ui {
class LogWindow;
}

class LogWindow : public QMainWindow
{
public:    
    ~LogWindow();
    void ClearLogs();
    static LogWindow& Instance(QWidget *parent = 0);
    void update(QString&);
private:
    explicit LogWindow(QWidget *parent = 0);
    LogWindow (const LogWindow&);
    LogWindow& operator=(const LogWindow&);
    static LogWindow *instance;

    Ui::LogWindow *ui;
};

#endif // LOGWINDOW_H
