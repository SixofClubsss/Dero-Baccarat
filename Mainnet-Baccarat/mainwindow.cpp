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
#include "rpc/rpc.h"
#include "help.h"
#include "dialog.h"


int Dialog::whichBet;
bool Dialog::betConfirmed;
QString rpc::walletAddress;
QString rpc::daemonAddress;
QString rpc::foundHandTXID;
bool rpc::foundHand;
double rpc::deroBalance;
double rpc::dReamBalance;
double rpc::totalHands;
double rpc::foundPlayerTotal;
double rpc::foundBankerTotal;
int rpc::playerWins;
int rpc::bankerWins;
int rpc::totalTies;
int rpc::foundPlayerX;
int rpc::foundPlayerY;
int rpc::foundPlayerZ;
int rpc::foundBankerX;
int rpc::foundBankerY;
int rpc::foundBankerZ;
int rpc::blockHeight;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFonts(QSysInfo::productType());
    startUp = true;
    rpc::walletConnected = false;
    rpc::daemonConnected = false;
    rpc::contractAddress = "8289c6109f41cbe1f6d5f27a419db537bf3bf30a25eff285241a36e1ae3e48a4";
    rpc::tokenAddress = "ad2e7b37c380cc1aed3a6b27224ddfc92a2d15962ca1f4d35e530dba0f9575a9";
    ui->daemonConnectedBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->daemonConnectedBox->setFocusPolicy(Qt::NoFocus);
    ui->walletConnectedBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->walletConnectedBox->setFocusPolicy(Qt::NoFocus);
    ui->deroBalanceDoubleSpinBox->setEnabled(false);
    ui->dReamBalanceDoubleSpinBox->setEnabled(false);
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
    blankCards();

    connect(ui->daemonRPCinput, SIGNAL(textChanged(QString)),
          this, SLOT(daemonToggle()));

    connect(ui->walletRPCinput, SIGNAL(textChanged(QString)),
          this, SLOT(walletToggle()));
}


MainWindow::~MainWindow()
{
    Worker::workThread.quit();
    delete ui;
}


void MainWindow::setFonts(QString os)
{

    int mcR1;
    int mcR2;
    int mcR3;
    int ubR;

    if(os == "macos" || os == "osx"){
        mcR1 = 22;
        mcR2 = 15;
        mcR3 = 18;
        ubR = 13;

    }else {
        mcR1 = 17;
        mcR2 = 11;
        mcR3 = 14;
        ubR = 10;
    }

    int fontId = QFontDatabase::addApplicationFont(":/fonts/Macondo-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont macondoRegular1(fontFamily);
    macondoRegular1.setPointSize(mcR1);
    macondoRegular1.setBold(true);
    ui->textBrowser->setFont(macondoRegular1);
    ui->textBrowser->setText("Welcome to dReam Tables Baccarat\n\nConnect Your Daemon & Wallet");
    QFont macondoRegular2(fontFamily);
    macondoRegular2.setPointSize(mcR2);
    macondoRegular2.setBold(true);

    ui->walletConnectedBox->setFont(macondoRegular2);
    ui->daemonConnectedBox->setFont(macondoRegular2);
    ui->minMaxLabel->setFont(macondoRegular2);
    ui->playerTotalSpinBox->setFont(macondoRegular2);
    ui->bankerTotalSpinBox->setFont(macondoRegular2);
    ui->pWinsSpinBox->setFont(macondoRegular2);
    ui->bWinsSpinBox->setFont(macondoRegular2);
    ui->explorerLabel->setFont(macondoRegular2);
    ui->tWinsSpinBox->setFont(macondoRegular2);
    ui->dsbTotalHandsPlayed->setFont(macondoRegular2);
    ui->heightSpinBox->setFont(macondoRegular2);

    QFont macondoRegular3(fontFamily);
    macondoRegular3.setPointSize(mcR3);
    macondoRegular3.setBold(true);
    ui->sessionsLabel->setFont(macondoRegular3);
    ui->exchangeLable->setFont(macondoRegular3);

    int fontId2 = QFontDatabase::addApplicationFont(":/fonts/Ubuntu-R.ttf");
    QString fontFamily2 = QFontDatabase::applicationFontFamilies(fontId2).at(0);
    QFont ubuntuRegular(fontFamily2);
    ubuntuRegular.setPointSize(ubR);
    ui->deroBalanceDoubleSpinBox->setFont(ubuntuRegular);
    ui->dReamBalanceDoubleSpinBox->setFont(ubuntuRegular);
    ui->playerButton->setFont(ubuntuRegular);
    ui->bankerButton->setFont(ubuntuRegular);
    ui->tieButton->setFont(ubuntuRegular);
    ui->playerBetAmount->setFont(ubuntuRegular);
    ui->bankerBetAmount->setFont(ubuntuRegular);
    ui->tieBetAmount->setFont(ubuntuRegular);
    ui->playerGroupBox->setFont(ubuntuRegular);
    ui->userpassInput->setFont(ubuntuRegular);
    ui->walletRPCinput->setFont(ubuntuRegular);
    ui->walletRPCbutton->setFont(ubuntuRegular);
    ui->daemonRPCinput->setFont(ubuntuRegular);
    ui->daemonRPCbutton->setFont(ubuntuRegular);
    ui->getChipButton->setFont(ubuntuRegular);
    ui->getChipsAmount->setFont(ubuntuRegular);
    ui->tradeChipButton->setFont(ubuntuRegular);
    ui->tradeChipsAmount->setFont(ubuntuRegular);
    ui->helpButton->setFont(ubuntuRegular);
    ui->logTextBrowser->setFont(ubuntuRegular);
    ui->searchButton->setFont(ubuntuRegular);
    ui->searchDoubleSpinBox->setFont(ubuntuRegular);

}

void MainWindow::buttonControl(bool b)
{
    ui->deroBalanceDoubleSpinBox->setEnabled(b);
    ui->dReamBalanceDoubleSpinBox->setEnabled(b);
    ui->playerButton->setEnabled(b);
    ui->bankerButton->setEnabled(b);
    ui->tieButton->setEnabled(b);
    ui->getChipButton->setEnabled(b);
    ui->tradeChipButton->setEnabled(b);
    ui->playerBetAmount->setEnabled(b);
    ui->bankerBetAmount->setEnabled(b);
    ui->tieBetAmount->setEnabled(b);
    ui->getChipsAmount->setEnabled(b);
    ui->tradeChipsAmount->setEnabled(b);
    ui->minMaxLabel->setEnabled(b);
}


void MainWindow::daemonToggle()     /// On daemon info change
{
    rpc::daemonAddress =  ui->daemonRPCinput->text();
    rpc::daemonConnected = false;
    ui->daemonConnectedBox->setChecked(false);
    ui->textBrowser->setText("Daemon Not Connected");
}


void MainWindow::walletToggle()     /// On wallet info change
{
    rpc::walletAddress = ui->walletRPCinput->text();
    rpc::rpcLogin = "null:null";
    ui->deroBalanceDoubleSpinBox->setValue(0);
    ui->dReamBalanceDoubleSpinBox->setValue(0);
    rpc::deroBalance = 0;
    rpc::dReamBalance = 0;
    rpc::walletConnected = false;
    buttonControl(false);
    ui->walletConnectedBox->setChecked(false);
    ui->textBrowser->setText("Wallet Not Connected");
}


void MainWindow::offset()       /// Offset timer
{
    QTime dieTime = QTime::currentTime().addMSecs(500);
    while (QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void MainWindow::refresh()      /// Updates Ui display
{
    offset();
    ui->heightSpinBox->setValue(rpc::blockHeight);
    ui->dsbTotalHandsPlayed->setValue(rpc::totalHands);
    ui->pWinsSpinBox->setValue(rpc::playerWins);
    ui->bWinsSpinBox->setValue(rpc::bankerWins);
    ui->tWinsSpinBox->setValue(rpc::totalTies);
    ui->searchDoubleSpinBox->setMinimum(rpc::totalHands-20);
    ui->searchDoubleSpinBox->setMaximum(rpc::totalHands);
    ui->deroBalanceDoubleSpinBox->setValue(rpc::deroBalance/100000);
    ui->dReamBalanceDoubleSpinBox->setValue(rpc::dReamBalance/100000);

    if(rpc::foundHand == true  && startUp == false){
        ui->textBrowser->setText("Displaying hand TXID: "+rpc::foundHandTXID);

        ui->playerTotalSpinBox->setValue(rpc::foundPlayerTotal);
        ui->playerXCardLabel->setPixmap(displayCards(rpc::foundPlayerX));
        ui->playerYCardLabel->setPixmap(displayCards(rpc::foundPlayerY));
        ui->playerZCardLabel->setPixmap(displayDrawCard(rpc::foundPlayerZ));

        ui->bankerTotalSpinBox->setValue(rpc::foundBankerTotal);
        ui->bankerXCardLabel->setPixmap(displayCards(rpc::foundBankerX));
        ui->bankerYCardLabel->setPixmap(displayCards(rpc::foundBankerY));
        ui->bankerZCardLabel->setPixmap(displayDrawCard(rpc::foundBankerZ));

        if(rpc::foundPlayerTotal > rpc::foundBankerTotal){
            ui->textBrowser->append("\nPlayer Wins");
            ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: rgba(79, 186, 196, 210); background-color: rgba(79, 186, 196, 21); };");
        }

        if(rpc::foundBankerTotal > rpc::foundPlayerTotal){
            ui->textBrowser->append("\nBanker Wins");
            ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: rgba(79, 186, 196, 210); background-color: rgba(79, 186, 196, 21); };");
        }

        if(rpc::foundBankerTotal == rpc::foundPlayerTotal){
            ui->textBrowser->append("\nTie");
            ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: rgba(56, 47, 165, 210); background-color: rgba(28, 31, 43, 0); };");
            ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: rgba(56, 47, 165, 210); background-color: rgba(28, 31, 43, 0); };");
        }
        ui->searchButton->setEnabled(true);
    }
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
    ui->textBrowser->setText("Trading Dero for dReams");   /// Readout to main text display
    Dialog::whichBet = 9;                               /// Which button was clicked
    Dialog D;                                         /// Pop up confirm bet menu
    D.setModal(true);
    D.exec();

    if(Dialog::betConfirmed == true){
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
    ui->textBrowser->setText("Trading dReams for Dero");
    Dialog::whichBet = 8;
    Dialog D;
    D.setModal(true);
    D.exec();

    if(Dialog::betConfirmed == true){
        tradeChips();
        Dialog::betConfirmed = false;

    }else {
        Dialog::betConfirmed = false;
        ui->textBrowser->setText("Select a option");
    }
}


void MainWindow::on_playerButton_clicked()
{
    startUp = true;
    ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgba(28, 31, 43, 0); };");
    ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgba(28, 31, 43, 0); };");
    readoutConfirm();
    blankCards();
    ui->textBrowser->setText("Confirm your Bet");
    Dialog::whichBet = 1;
    Dialog D;
    D.setModal(true);
    D.exec();

    if(Dialog::betConfirmed == true){
        ui->searchButton->setEnabled(false);
        rpc::foundHand = false;
        playerBet();
        Dialog::betConfirmed = false;
        startUp = false;

    }else {
        ui->searchButton->setEnabled(true);
        Dialog::betConfirmed = false;
        ui->textBrowser->setText("Select a option");
        blankCards();
    }
}


void MainWindow::on_bankerButton_clicked()
{
    startUp = true;
    ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgba(28, 31, 43, 0); };");
    ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgba(28, 31, 43, 0); };");
    readoutConfirm();
    blankCards();
    ui->textBrowser->setText("Confirm your Bet");
    Dialog::whichBet = 2;
    Dialog D;
    D.setModal(true);
    D.exec();

    if(Dialog::betConfirmed == true){
        ui->searchButton->setEnabled(false);
        rpc::foundHand = false;
        bankerBet();
        Dialog::betConfirmed = false;
        startUp = false;

    }else {
        ui->searchButton->setEnabled(true);
        Dialog::betConfirmed = false;
        ui->textBrowser->setText("Select a option");
        blankCards();
    }
}


void MainWindow::on_tieButton_clicked()
{
    startUp = true;
    ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgba(28, 31, 43, 0); };");
    ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgba(28, 31, 43, 0); };");
    readoutConfirm();
    blankCards();
    ui->textBrowser->setText("Confirm your Bet");
    Dialog::whichBet = 3;
    Dialog D;
    D.setModal(true);
    D.exec();

    if(Dialog::betConfirmed == true){
        ui->searchButton->setEnabled(false);
        rpc::foundHand = false;
        tieBet();
        Dialog::betConfirmed = false;
        startUp = false;

    }else {
        ui->searchButton->setEnabled(true);
        Dialog::betConfirmed = false;
        ui->textBrowser->setText("Select a option");
        blankCards();
    }
}


void MainWindow::on_searchButton_clicked()
{
    startUp = true;
    ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgba(28, 31, 43, 0); };");
    ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgba(28, 31, 43, 0); };");
    searchHandData();
}
