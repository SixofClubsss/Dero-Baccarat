#include "mainwindow.h"
#include "helpmenu.h"
#include "QApplication"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    helpmenu helpmenu;
    helpmenu.setModal(true);
    helpmenu.exec();

    MainWindow w;
    ///w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}
