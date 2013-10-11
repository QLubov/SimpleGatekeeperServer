#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once


#include <QMainWindow>
#include <QFileDialog>

//#include "endpoint.h"
//#include <h323.h>
//#include "gatekeeperserver.h"
//#include <logwindow.h>
//#include <xmlreader.h>
//#include "actionmanager.h"
#include "qserverthread.h"

//void run();
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    void ClearLogs();
    Ui::MainWindow *ui;
    XMLReader xml;
    std::queue<Command*>* commands;        
private slots:
    void startScenario();
    void stopScenario();
    void updateLogs(QString);
signals:
    void exit();
};

#endif // MAINWINDOW_H
