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

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "rpc.h"
#include "help.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "QSizePolicy"
#include "QTimer"

using std::string;
int Dialog::whichBet;
bool Dialog::betConfirmed;
bool rpc::foundHand;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(refresh()));
    timer->start(9000);

    ui->playerXCardLabel->setPixmap(QPixmap(":/CardBack"));
    ui->playerYCardLabel->setPixmap(QPixmap(":/CardBack"));
    ui->playerZCardLabel->setPixmap(QPixmap(":/CardBack"));
    ui->bankerXCardLabel->setPixmap(QPixmap(":/CardBack"));
    ui->bankerYCardLabel->setPixmap(QPixmap(":/CardBack"));
    ui->bankerZCardLabel->setPixmap(QPixmap(":/CardBack"));
    ui->daemonConnectedBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->daemonConnectedBox->setFocusPolicy(Qt::NoFocus);
    ui->walletConnectedBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->walletConnectedBox->setFocusPolicy(Qt::NoFocus);
    ui->playerButton->setEnabled(false);
    ui->bankerButton->setEnabled(false);
    ui->tieButton->setEnabled(false);
    ui->getChipButton->setEnabled(false);
    ui->tradeChipButton->setEnabled(false);
    ui->playerBetAmount->setEnabled(false);
    ui->bankerBetAmount->setEnabled(false);
    ui->tieBetAmount->setEnabled(false);
    ui->getChipsAmount->setEnabled(false);
    ui->tradeChipsAmount->setEnabled(false);
    ui->minMaxLabel->setEnabled(false);
    ui->textBrowser->setText("Welcome to the Testnet Table\n\nConnect Your Daemon & Wallet");
    fetchScData();
    blankCards();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::refresh()
{
    fetchScData();
}


void MainWindow::on_helpButton_clicked()
{
    Help H;
    H.setModal(true);
    H.exec();
}

void MainWindow::on_daemonRPCbutton_clicked(bool checked)
{
    checkDaemon();
}


void MainWindow::on_walletRPCbutton_clicked(bool checked)
{
    checkWallet();
}


void MainWindow::on_getChipButton_clicked()
{
    readoutConfirm();
    ui->textBrowser->setText("Trading Dero for Chips");   /// Readout to main text display
    Dialog::whichBet = 9;                               /// Which button was clicked
    Dialog D;                                         /// Pop up confirm bet menu
    D.setModal(true);
    D.exec();

    if(Dialog::betConfirmed == true)
    {
        getChips();                             /// If confirmed you will place bet
        Dialog::betConfirmed = false;

    }else {
        Dialog::betConfirmed = false;
        ui->textBrowser->setText("Select a option");
    }
}


void MainWindow::on_tradeChipButton_clicked()
{
    readoutConfirm();
    ui->textBrowser->setText("Trading Chips for Dero");
    Dialog::whichBet = 8;
    Dialog D;
    D.setModal(true);
    D.exec();

    if(Dialog::betConfirmed == true)
    {
        tradeChips();
        Dialog::betConfirmed = false;

    }else {
        Dialog::betConfirmed = false;
        ui->textBrowser->setText("Select a option");
    }
}

void MainWindow::findMyHand()    /// Find hand on explorer
{
    int i = 0;
    do{
    fetchHandData();
    rpc::thisHand++;
    i++;
        if(i == 45)
        {
          ui->textBrowser->append("Waiting for Block...");
          blankCards();
        }
    }while(rpc::foundHand == false && i < 45);


    if(rpc::foundHand == false)   /// Retry if it did not find hand
    {
        delay();
        rpc::thisHand = rpc::thisHand - 51;
        int ii = 0;
        do{
        fetchHandData();
        rpc::thisHand++;
        ii++;
            if(ii == 20)
            {
              ui->textBrowser->setText("Error Could Not Find Hand\n\nCheck TXID on Explorer or Search for Hand #");
              blankCards();
            }
        }while(rpc::foundHand == false && ii < 20);
    }
     ui->searchButton->setEnabled(true);
     ui->searchDoubleSpinBox->setValue(rpc::thisHand-5);
}


void MainWindow::on_playerButton_clicked()
{
    ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgb(28, 31, 43, 0); };");
    ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgb(28, 31, 43, 0); };");
    readoutConfirm();
    blankCards();
    ui->textBrowser->setText("Confirm your Bet");
    Dialog::whichBet = 1;
    Dialog D;
    D.setModal(true);
    D.exec();

    if(Dialog::betConfirmed == true)
    {
        ui->searchButton->setEnabled(false);
        fetchScData();
        rpc::foundHand = false;
        playerBet();
        Dialog::betConfirmed = false;
        delay();
        findMyHand();

    }else {
        ui->searchButton->setEnabled(true);
        Dialog::betConfirmed = false;
        ui->textBrowser->setText("Select a option");
        blankCards();
    }
}


void MainWindow::on_bankerButton_clicked()
{
    ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgb(28, 31, 43, 0); };");
    ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgb(28, 31, 43, 0); };");
    readoutConfirm();
    blankCards();
    ui->textBrowser->setText("Confirm your Bet");
    Dialog::whichBet = 2;
    Dialog D;
    D.setModal(true);
    D.exec();

    if(Dialog::betConfirmed == true)
    {
        ui->searchButton->setEnabled(false);
        fetchScData();
        rpc::foundHand = false;
        bankerBet();
        Dialog::betConfirmed = false;
        delay();
        findMyHand();

    }else {
        ui->searchButton->setEnabled(true);
        Dialog::betConfirmed = false;
        ui->textBrowser->setText("Select a option");
        blankCards();
    }
}


void MainWindow::on_tieButton_clicked()
{
    ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgb(28, 31, 43, 0); };");
    ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgb(28, 31, 43, 0); };");
    readoutConfirm();
    blankCards();
    ui->textBrowser->setText("Confirm your Bet");
    Dialog::whichBet = 3;
    Dialog D;
    D.setModal(true);
    D.exec();

    if(Dialog::betConfirmed == true)
    {
        ui->searchButton->setEnabled(false);
        fetchScData();
        rpc::foundHand = false;
        tieBet();
        Dialog::betConfirmed = false;
        delay();
        findMyHand();

    }else {
        ui->searchButton->setEnabled(true);
        Dialog::betConfirmed = false;
        ui->textBrowser->setText("Select a option");
        blankCards();
    }
}


void MainWindow::on_reloadButton_clicked()   /// Reload SC data
{
    fetchScData();
}


void MainWindow::on_searchButton_clicked()
{
    ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgb(28, 31, 43, 0); };");
    ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgb(28, 31, 43, 0); };");
    searchHandData();
}
