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

#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rpc/rpc.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setFonts(QSysInfo::productType());

    if(Dialog::whichBet == 1){
         playerConfirmText();

    }else if(Dialog::whichBet == 2){
        bankerConfirmText();                /// Confirm menu will look at which button was clicked

    }else if(Dialog::whichBet == 3){
        tieConfirmText();

    }else if(Dialog::whichBet == 8){
        tradeConfirmText();

    }else if(Dialog::whichBet == 9){
        getConfirmText();
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setFonts(QString os)
{  
    int mcR;
    int ubR;

    if(os == "macos" || os == "osx"){
        mcR = 18;
        ubR = 12;
    }else {
        mcR = 14;
        ubR = 10;
    }

    int fontId = QFontDatabase::addApplicationFont(":/fonts/Macondo-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont macondoRegular(fontFamily);
    macondoRegular.setPointSize(mcR);
    macondoRegular.setBold(true);
    ui->dReamsLabel->setFont(macondoRegular);
    ui->confirmTextBrowser->setFont(macondoRegular);

    int fontId2 = QFontDatabase::addApplicationFont(":/fonts/Ubuntu-R.ttf");
    QString fontFamily2 = QFontDatabase::applicationFontFamilies(fontId2).at(0);
    QFont ubuntuRegular(fontFamily2);
    ubuntuRegular.setPointSize(ubR);
    ui->buttonBox->setFont(ubuntuRegular);
}


void Dialog::on_buttonBox_accepted()
{
    Dialog::betConfirmed = true;       /// To confirm and place bet
}


void Dialog::playerConfirmText()   /// Read out for each bet
{
    ui->confirmTextBrowser->setText("You are about to bet "+readout::playerAmount+" dReams on Player\n\nPayout is 1:1\n\nClick Ok to confirm this bet");
}


void Dialog::bankerConfirmText()
{
    ui->confirmTextBrowser->setText("You are about to bet "+readout::bankerAmount+" dReams on Banker\n\nPayout is 0.95:1\n(House takes 5% commission)\n\nClick Ok to confirm this bet");
}


void Dialog::tieConfirmText()
{
    ui->confirmTextBrowser->setText("You are about to bet "+readout::tieAmount+" dReams on Tie\n\nPayout is 8:1\n\nClick Ok to confirm this bet");
}


void Dialog::getConfirmText()
{
    ui->confirmTextBrowser->setText("You are about to trade "+readout::deroAmount+" Dero for "+readout::deroConverted+" dReams\n\nClick Ok to confirm this action");
}


void Dialog::tradeConfirmText()
{
    ui->confirmTextBrowser->setText("You are about to trade "+readout::chipAmount+" dReams for "+readout::chipsConverted+" Dero\n\nClick Ok to confirm this action");
}
