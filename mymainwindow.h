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

private:
    void ClearLogs();
    Ui::MyMainWindow *ui;
    XMLReader xml;
    std::queue<Command*>* commands;
    //QFile scenario;
    QString *nameOfScenario;
    std::string name;
private slots:
    void startScenario();
    void stopScenario();
    void updateLogs(QString);
    void openFile();
    void editFile();
    void saveLogs();
signals:
    void exit();
};

#endif // MYMAINWINDOW_H
