#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QProcess>
#include <QStringList>
#include "qserverthread.h"

namespace Ui {
class MyMainWindow;
}

class MyMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MyMainWindow(QWidget *parent = 0);
    ~MyMainWindow();    
private slots:
    void startScenario();
    void stopScenario();
    void updateLogs(const QString&);
    void openFile();
    void editFile();
    void saveLogs();
signals:
    void StopServer();
private:
    void ClearLogs();
    Ui::MyMainWindow *ui;
    QString nameOfScenario;
    void SetButtonsState(bool editButton, bool saveButton, bool startButton, bool stopButton);
};

#endif // MYMAINWINDOW_H
