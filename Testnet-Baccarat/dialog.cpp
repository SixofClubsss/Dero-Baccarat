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
#include "rpc.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    if(Dialog::whichBet == 1)
    {
         playerConfirmText();

    }else if(Dialog::whichBet == 2)
    {
        bankerConfirmText();                /// Confirm menu will look at which button was clicked

    }else if(Dialog::whichBet == 3)
    {
        tieConfirmText();

    }else if(Dialog::whichBet == 8)
    {
        tradeConfirmText();

    }else if(Dialog::whichBet == 9)
    {
        getConfirmText();
    }
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_buttonBox_accepted()
{
    Dialog::betConfirmed = true;       /// To confirm and place bet
}

void Dialog::playerConfirmText()   /// Read out for each bet
{
    ui->confirmTextBrowser->setText("You are about to bet "+readout::playerAmount+" dChips on Player\n\nPayout is 1:1\n\nClick Ok to confirm this bet");
}

void Dialog::bankerConfirmText()
{
    ui->confirmTextBrowser->setText("You are about to bet "+readout::bankerAmount+" dChips on Banker\n\nPayout is 0.95:1\n(House takes 5% commission)\n\nClick Ok to confirm this bet");
}

void Dialog::tieConfirmText()
{
    ui->confirmTextBrowser->setText("You are about to bet "+readout::tieAmount+" dChips on Tie\n\nPayout is 8:1\n\nClick Ok to confirm this bet");
}


void Dialog::getConfirmText()
{
    ui->confirmTextBrowser->setText("You are about to trade "+readout::deroAmount+" Dero for "+readout::deroConverted+" dChips\n\nClick Ok to confirm this bet");
}


void Dialog::tradeConfirmText()
{
    ui->confirmTextBrowser->setText("You are about to trade "+readout::chipAmount+" dChips for "+readout::chipsConverted+" Dero\n\nClick Ok to confirm this bet");
}
