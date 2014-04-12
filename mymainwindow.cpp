#include "mymainwindow.h"
#include "ui_mymainwindow.h"

MyMainWindow::MyMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyMainWindow)
{    
    ui->setupUi(this);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

void MyMainWindow::startScenario()
{
    ClearLogs();    
    if(!nameOfScenario->isEmpty())
    {
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(false);
        QFile *file = new QFile(*nameOfScenario);
        QServerThread *thread = new QServerThread(this);
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), this, SLOT(stopScenario()));
        connect(thread, SIGNAL(update(QString)), this, SLOT(updateLogs(QString)));
        connect(this, SIGNAL(exit()), thread, SLOT(end()));
        thread->StartThread(file);
    }

}
void MyMainWindow::stopScenario()
{
    emit exit();
    ui->pushButton_4->setEnabled(true);
}
void MyMainWindow::updateLogs(QString Message)
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText() + Message + "\n");
}
void MyMainWindow::ClearLogs()
{
    ui->textBrowser->clear();
}
void MyMainWindow::openFile()
{
    nameOfScenario = new QString (QFileDialog::getOpenFileName(this, "Choose file", "d:/", "XML-files (*.xml)"));
    ui->pushButton_2->setEnabled(true);    
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_5->setEnabled(true);    
}
void MyMainWindow::editFile()
{
    QProcess *proc = new QProcess(this);
    QStringList arg;
    arg.append(*nameOfScenario);
    proc->start("write.exe",arg);
}
void MyMainWindow::saveLogs()
{
    QString name = QFileDialog::getOpenFileName(this, "Choose file ", "d:/", "TXT-files (*.txt)");
    QFile *logFile = new QFile(name);
    logFile->open(QIODevice::Append | QIODevice::Text);
    QTextStream out(logFile);
    out<<ui->textBrowser->toPlainText();
    logFile->close();    
}
