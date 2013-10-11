#include "mainwindow.h"
#include <QApplication>
//#include "xmlreader.h"
#include <h323.h>
//#include "h323ep.h"
#include <ptlib.h>

using namespace std;

class form : public PProcess
{
    PCLASSINFO(form, PProcess)
public:
    void Main();
};

PCREATE_PROCESS(form)

void form::Main()
//int main(int argc, char *argv[])
{
    int argc;
    char *argv[1];
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    /*return*/ a.exec();
}
