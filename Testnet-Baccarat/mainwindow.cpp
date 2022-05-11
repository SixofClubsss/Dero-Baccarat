#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "rpc.h"
#include "help.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "QSizePolicy"
#include "QTimer"
#include "QProgressBar"

using std::string;
int Dialog::whichBet;
bool Dialog::betConfirmed;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(refresh()));
    timer->start(6000);

    /*QPixmap bkgnd(":/background");
    bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);*/

    ui->playerXCardLabel->setPixmap(QPixmap(":/CardBack"));
    ui->playerYCardLabel->setPixmap(QPixmap(":/CardBack"));
    ui->playerZCardLabel->setPixmap(QPixmap(":/CardBack"));

    ui->bankerXCardLabel->setPixmap(QPixmap(":/CardBack"));
    ui->bankerYCardLabel->setPixmap(QPixmap(":/CardBack"));
    ui->bankerZCardLabel->setPixmap(QPixmap(":/CardBack"));

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
    ui->textBrowser->setText("Trading Dero for Chips");   /// Readout to main tesxt display
    Dialog::whichBet = 9;                          /// Which button was clicked
    Dialog D;                          /// Pop up confirm bet menu
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


void MainWindow::on_playerButton_clicked()
{
    readoutConfirm();
    blankCards();
    ui->textBrowser->setText("Confirm your Bet");
    Dialog::whichBet = 1;
    Dialog D;
    D.setModal(true);
    D.exec();

    if(Dialog::betConfirmed == true)
    {
        playerBet();
        Dialog::betConfirmed = false;
        delay();
        fetchScData();
        fetchHandData();

    }else {
        Dialog::betConfirmed = false;
        ui->textBrowser->setText("Select a option");
        blankCards();
    }

}


void MainWindow::on_bankerButton_clicked()
{
    readoutConfirm();
    blankCards();
    ui->textBrowser->setText("Confirm your Bet");
    Dialog::whichBet = 2;
    Dialog D;
    D.setModal(true);
    D.exec();

    if(Dialog::betConfirmed == true)
    {
        bankerBet();
        Dialog::betConfirmed = false;
        delay();
        fetchScData();
        fetchHandData();

    }else {
        Dialog::betConfirmed = false;
        ui->textBrowser->setText("Select a option");
        blankCards();
    }
}


void MainWindow::on_tieButton_clicked()
{
    readoutConfirm();
    blankCards();
    ui->textBrowser->setText("Confirm your Bet");
    Dialog::whichBet = 3;
    Dialog D;
    D.setModal(true);
    D.exec();

    if(Dialog::betConfirmed == true)
    {
        tieBet();
        Dialog::betConfirmed = false;
        delay();
        fetchScData();
        fetchHandData();

    }else {
        Dialog::betConfirmed = false;
        ui->textBrowser->setText("Select a option");
        blankCards();
    }
}


void MainWindow::on_reloadButton_clicked()   /// Reload SC data
{
    fetchScData();
}
