#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "rpc.h"
#include "helpmenu.h"
#include "confirmmenu.h"
#include "ui_confirmmenu.h"
#include "QSizePolicy"

using std::string;

int confirmmenu::whichBet;
bool confirmmenu::betConfirmed;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->daemonConnectedBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->ui->daemonConnectedBox->setFocusPolicy(Qt::NoFocus);
    this->ui->walletConnectedBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->ui->walletConnectedBox->setFocusPolicy(Qt::NoFocus);
    ui->label->setScaledContents(true);
    ui->textBrowser->setText("Welcome, thanks for testing.");
    fetchScData();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_helpButton_clicked()
{
    helpmenu helpmenu;
    helpmenu.setModal(true);
    helpmenu.exec();
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
    ui->textBrowser->setText("Trading Dero for Chips");   /// Readout to main tesxt display
    confirmmenu::whichBet = 9;                          /// Which button was clicked
    confirmmenu confirmmenu;                          /// Pop up confirm bet menu
    confirmmenu.setModal(true);
    confirmmenu.exec();

    if(confirmmenu::betConfirmed == true)
    {
        getChips();                             /// If confirmed you will place bet
        confirmmenu::betConfirmed = false;

    }else {
        confirmmenu::betConfirmed = false;
        ui->textBrowser->setText("Select a option");
    }
}


void MainWindow::on_tradeChipButton_clicked()
{
    ui->textBrowser->setText("Trading Chips for Dero");
    confirmmenu::whichBet = 8;
    confirmmenu confirmmenu;
    confirmmenu.setModal(true);
    confirmmenu.exec();

    if(confirmmenu::betConfirmed == true)
    {
        tradeChips();
        confirmmenu::betConfirmed = false;

    }else {
        confirmmenu::betConfirmed = false;
        ui->textBrowser->setText("Select a option");
    }
}


void MainWindow::on_playerButton_clicked()
{
    ui->textBrowser->setText("Confirm your Bet");
    confirmmenu::whichBet = 1;
    confirmmenu confirmmenu;
    confirmmenu.setModal(true);
    confirmmenu.exec();

    if(confirmmenu::betConfirmed == true)
    {
        playerBet();
        confirmmenu::betConfirmed = false;
        delay();
        fetchScData();

    }else {
        confirmmenu::betConfirmed = false;
        ui->textBrowser->setText("Select a option");
    }

}


void MainWindow::on_bankerButton_clicked()
{
    ui->textBrowser->setText("Confirm your Bet");
    confirmmenu::whichBet = 2;
    confirmmenu confirmmenu;
    confirmmenu.setModal(true);
    confirmmenu.exec();

    if(confirmmenu::betConfirmed == true)
    {
        bankerBet();
        confirmmenu::betConfirmed = false;
        delay();
        fetchScData();

    }else {
        confirmmenu::betConfirmed = false;
        ui->textBrowser->setText("Select a option");
    }
}


void MainWindow::on_tieButton_clicked()
{
    ui->textBrowser->setText("Confirm your Bet");
    confirmmenu::whichBet = 3;
    confirmmenu confirmmenu;
    confirmmenu.setModal(true);
    confirmmenu.exec();

    if(confirmmenu::betConfirmed == true)
    {
        tieBet();
        confirmmenu::betConfirmed = false;
        delay();
        fetchScData();

    }else {
        confirmmenu::betConfirmed = false;
        ui->textBrowser->setText("Select a option");
    }
}


void MainWindow::on_reloadButton_clicked()   /// Reload SC data
{
    fetchScData();
}
