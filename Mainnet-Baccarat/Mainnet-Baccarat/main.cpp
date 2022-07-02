#include "mainwindow.h"
#include "help.h"
#include "rpc/rpc.h"
#include "QApplication"

QThread Worker::workThread;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTimer timer;
    Worker worker;

    Help H;
    H.setModal(true);
    H.exec();

    MainWindow w;
    w.show();

    QObject::connect(&timer, SIGNAL(timeout()), &worker, SLOT(onTimeout()));
    timer.start(9000);
    QObject::connect(&timer, SIGNAL(timeout()), &w, SLOT(refresh()));

    worker.moveToThread(&Worker::workThread);
    Worker::workThread.start();

    return a.exec();
}
