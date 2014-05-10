#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include <QFileDialog>
#include <QProcess>
#include <QTextStream>
#include <QFile>
#include "logmanager.h"
#include "qservermanager.h"

MyMainWindow::MyMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyMainWindow),
    mServerManager(new QServerManager())
{    
    ui->setupUi(this);
    SetButtonsState(false, false, false, false);

    connect(&LogManager::Instance(), SIGNAL(updateLogs(const QString&)), this, SLOT(updateLogs(const QString&)));
}

MyMainWindow::~MyMainWindow()
{
    delete mServerManager;
    delete ui;
}

void MyMainWindow::startScenario()
{
    ClearLogTextBrowser();
    if(!nameOfScenario.isEmpty())
    {
        SetButtonsState(true, true, false, true);
        mServerManager->InitServer(nameOfScenario);
    }

}
void MyMainWindow::stopScenario(const QString& message)
{
    mServerManager->OnTerminate(message);
    SetButtonsState(true, true, true, false);
}
void MyMainWindow::updateLogs(const QString& Message)
{
    std::cout<<"update logs::"<<Message.toStdString()<<std::endl;
    ui->textBrowser->setText(ui->textBrowser->toPlainText() + Message + "\n");
}
void MyMainWindow::ClearLogTextBrowser()
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

