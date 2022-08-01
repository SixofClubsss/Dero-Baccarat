#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "rpc/rpc.h"
#include "help.h"
#include "dialog.h"


using std::string;
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
    startUp = true;
    rpc::walletConnected = false;
    rpc::daemonConnected = false;
    rpc::contractAddress = "8289c6109f41cbe1f6d5f27a419db537bf3bf30a25eff285241a36e1ae3e48a4";
    rpc::tokenAddress = "ad2e7b37c380cc1aed3a6b27224ddfc92a2d15962ca1f4d35e530dba0f9575a9";
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
    setFonts();
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


void MainWindow::setFonts()
{
    int fontId = QFontDatabase::addApplicationFont(":/fonts/Macondo-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont macondoRegular17(fontFamily);
    macondoRegular17.setPointSize(17);
    macondoRegular17.setBold(true);
    ui->textBrowser->setFont(macondoRegular17);
    ui->textBrowser->setText("Welcome to dReam Tables Baccarat\n\nConnect Your Daemon & Wallet");
    QFont macondoRegular12(fontFamily);
    macondoRegular12.setPointSize(11);
    macondoRegular12.setBold(true);

    ui->walletConnectedBox->setFont(macondoRegular12);
    ui->daemonConnectedBox->setFont(macondoRegular12);
    ui->minMaxLabel->setFont(macondoRegular12);
    ui->playerTotalSpinBox->setFont(macondoRegular12);
    ui->bankerTotalSpinBox->setFont(macondoRegular12);
    ui->pWinsSpinBox->setFont(macondoRegular12);
    ui->bWinsSpinBox->setFont(macondoRegular12);
    ui->explorerLabel->setFont(macondoRegular12);
    ui->tWinsSpinBox->setFont(macondoRegular12);
    ui->dsbTotalHandsPlayed->setFont(macondoRegular12);
    ui->heightSpinBox->setFont(macondoRegular12);

    QFont macondoRegular14(fontFamily);
    macondoRegular14.setPointSize(14);
    macondoRegular14.setBold(true);
    ui->sessionsLabel->setFont(macondoRegular14);
    ui->exchangeLable->setFont(macondoRegular14);

    int fontId2 = QFontDatabase::addApplicationFont(":/fonts/Ubuntu-R.ttf");
    QString fontFamily2 = QFontDatabase::applicationFontFamilies(fontId2).at(0);
    QFont ubuntuRegular(fontFamily2);
    ubuntuRegular.setPointSize(10);
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
       ui->playerXCardLabel->setPixmap(displayPlayerCards(rpc::foundPlayerX));
       ui->playerYCardLabel->setPixmap(displayPlayerCards(rpc::foundPlayerY));
       ui->playerZCardLabel->setPixmap(displayDrawPlayerCard(rpc::foundPlayerZ));

       ui->bankerTotalSpinBox->setValue(rpc::foundBankerTotal);
       ui->bankerXCardLabel->setPixmap(displayBankerCards(rpc::foundBankerX));
       ui->bankerYCardLabel->setPixmap(displayBankerCards(rpc::foundBankerY));
       ui->bankerZCardLabel->setPixmap(displayDrawBankerCard(rpc::foundBankerZ));

       if(rpc::foundPlayerTotal > rpc::foundBankerTotal){
            ui->textBrowser->append("\nPlayer Wins");
            ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: rgb(79, 186, 196, 210); background-color: rgb(79, 186, 196, 21); };");
       }

       if(rpc::foundBankerTotal > rpc::foundPlayerTotal){
            ui->textBrowser->append("\nBanker Wins");
            ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: rgb(79, 186, 196, 210); background-color: rgb(79, 186, 196, 21); };");
       }

       if(rpc::foundBankerTotal == rpc::foundPlayerTotal){
            ui->textBrowser->append("\nTie");
            ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: rgb(56, 47, 165, 210); background-color: rgb(28, 31, 43, 0); };");
            ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: rgb(56, 47, 165, 210); background-color: rgb(28, 31, 43, 0); };");
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
    ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgb(28, 31, 43, 0); };");
    ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgb(28, 31, 43, 0); };");
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
    ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgb(28, 31, 43, 0); };");
    ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgb(28, 31, 43, 0); };");
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
    ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgb(28, 31, 43, 0); };");
    ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgb(28, 31, 43, 0); };");
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
    ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgb(28, 31, 43, 0); };");
    ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: white; background-color: rgb(28, 31, 43, 0); };");
    searchHandData();
}
