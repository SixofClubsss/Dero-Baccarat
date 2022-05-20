#include "mainwindow.h"
#include "help.h"
#include "QApplication"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Help H;
    H.setModal(true);
    H.exec();
    MainWindow w;
    w.show();
    return a.exec();
}
