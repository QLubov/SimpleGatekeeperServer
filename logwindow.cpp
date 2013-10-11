#include "logwindow.h"
#include "ui_logwindow.h"

LogWindow* LogWindow::instance = 0;

LogWindow::LogWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LogWindow)
{
    ui->setupUi(this);
}

LogWindow::~LogWindow()
{
    delete ui;
    ui = 0;
}
void LogWindow::update(QString &Message)
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText() + "\n" + Message);
}
void LogWindow::ClearLogs()
{
    ui->textBrowser->clear();
}
LogWindow& LogWindow::Instance(QWidget *parent)
{
    if(!instance)
        instance = new LogWindow(parent);
    return *instance;
}

