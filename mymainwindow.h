#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>

class QServerManager;

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
    void StartButtonEnable();
    void ServerFinished(bool success);

signals:
    void StopServer();
private:
    void ClearLogTextBrowser();
    Ui::MyMainWindow *ui;
    QString nameOfScenario;
    void SetButtonsState(bool editButton, bool saveButton, bool startButton, bool stopButton);
    //TODO: investagate why object cann't be created as value type
    QServerManager *mServerManager;
};

#endif // MYMAINWINDOW_H
