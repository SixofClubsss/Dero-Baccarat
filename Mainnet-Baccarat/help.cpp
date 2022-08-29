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

#include "help.h"
#include "ui_help.h"
#include "mainwindow.h"

Help::Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    setFonts(QSysInfo::productType());

    qInfo() << ("\033[36m♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤\033[0m");
    qInfo() << ("\033[36m    dReam Tables Baccarat\033[0m");
    qInfo() << ("\033[36m   https://dreamtables.net\033[0m");
    qInfo() << ("\033[36m     © 2022 dReam Tables\033[0m");
    qInfo() << ("\033[36m♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤\033[0m");
}

Help::~Help()
{
    delete ui;
}

void Help::setFonts(QString os)
{
    int mcR;
    int ubR;

    if(os == "macos"){
        mcR = 18;
        ubR = 12;
    }else {
        mcR = 11;
        ubR = 10;
    }

    int fontId = QFontDatabase::addApplicationFont(":/fonts/Macondo-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont macondoRegular(fontFamily);
    macondoRegular.setPointSize(mcR);
    macondoRegular.setBold(true);
    ui->dReamsLabel->setFont(macondoRegular);

    int fontId2 = QFontDatabase::addApplicationFont(":/fonts/Ubuntu-R.ttf");
    QString fontFamily2 = QFontDatabase::applicationFontFamilies(fontId2).at(0);
    QFont ubuntuRegular(fontFamily2);
    ubuntuRegular.setPointSize(ubR);
    ui->buttonBox->setFont(ubuntuRegular);

}
