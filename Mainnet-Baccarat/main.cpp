/*
dReam Tables Dero Baccarat
Copyright (C) 2022  dReam Tables

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

Always play responsibly.

https://dreamtables.net
*/

#include "QApplication"
#include "mainwindow.h"
#include "help.h"
#include "rpc/rpc.h"

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
