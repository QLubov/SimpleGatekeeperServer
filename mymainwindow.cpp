#include "mymainwindow.h"
#include "ui_mymainwindow.h"

MyMainWindow::MyMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyMainWindow)
{    
    ui->setupUi(this);
    SetButtonsState(false, false, false, false);

    connect(&LogManager::Instance(), SIGNAL(updateLogs(QString)), this, SLOT(updateLogs(const QString&)));
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

void MyMainWindow::startScenario()
{
    ClearLogs();    
    if(!nameOfScenario.isEmpty())
    {

        SetButtonsState(true, true, false, true);

        QServerThread *thread = new QServerThread(nameOfScenario, this);

        connect(thread, SIGNAL(finished()), this, SLOT(StartButtonEnable()));        
        connect(this, SIGNAL(StopServer()), thread, SLOT(StopServer()));
        thread->start();

        LOG("Scenario " + nameOfScenario + " opened");
    }

}
void MyMainWindow::stopScenario()
{
    emit StopServer();
}
void MyMainWindow::updateLogs(const QString& Message)
{
    std::cout<<"update logs::"<<Message.toStdString()<<std::endl;
    ui->textBrowser->setText(ui->textBrowser->toPlainText() + Message + "\n");
}
void MyMainWindow::ClearLogs()
{
    ui->textBrowser->clear();
}

void MyMainWindow::SetButtonsState(bool editButton, bool saveButton, bool startButton, bool stopButton)
{
    ui->EditButton->setEnabled(editButton);
    ui->SaveButton->setEnabled(saveButton);
    ui->StartButton->setEnabled(startButton);
    ui->StopButton->setEnabled(stopButton);
}
void MyMainWindow::openFile()
{
    nameOfScenario = QFileDialog::getOpenFileName(this, "Choose file", "d:/", "XML-files (*.xml)");
    SetButtonsState(true, true, true, false);
}
void MyMainWindow::editFile()
{
    QProcess *proc = new QProcess(this);
    connect(proc, SIGNAL(finished(int)), proc, SLOT(deleteLater()));
    QStringList arg;
    arg.append(nameOfScenario);
    proc->start("write.exe",arg);
}
void MyMainWindow::saveLogs()
{
    QString name = QFileDialog::getOpenFileName(this, "Choose file ", "d:/", "TXT-files (*.txt)");
    if(name.isEmpty())
        return;
    QFile logFile(name);
    logFile.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&logFile);
    out<<ui->textBrowser->toPlainText();
    logFile.close();
}

void MyMainWindow::StartButtonEnable()
{
    SetButtonsState(true, true, true, false);
}
