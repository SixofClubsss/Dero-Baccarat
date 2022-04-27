#include "confirmmenu.h"
#include "ui_confirmmenu.h"


confirmmenu::confirmmenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirmmenu)
{
    ui->setupUi(this);
    if(confirmmenu::whichBet == 1)
    {
         playerConfirmText();

    }else if(confirmmenu::whichBet == 2)
    {
        bankerConfirmText();                /// Confirm menu will look at which button was clicked

    }else if(confirmmenu::whichBet == 3)
    {
        tieConfirmText();

    }else if(confirmmenu::whichBet == 8)
    {
        tradeConfirmText();

    }else if(confirmmenu::whichBet == 9)
    {
        getConfirmText();
    }
}


confirmmenu::~confirmmenu()
{
    delete ui;
}


void confirmmenu::on_buttonBox_accepted()
{
    confirmmenu::betConfirmed = true;       /// To confirm and place bet
}

void confirmmenu::playerConfirmText()   /// Read out for each bet
{
    ui->confirmTextBrowser->setText("You are about to bet 0.1 Chips on Player\n\nPayout is 1:1\n\nClick Ok to confirm this bet");
}

void confirmmenu::bankerConfirmText()
{
    ui->confirmTextBrowser->setText("You are about to bet 0.1 Chips on Banker\n\nPayout is 0.95:1\n(House takes 5% commission)\n\nClick Ok to confirm this bet");
}

void confirmmenu::tieConfirmText()
{
    ui->confirmTextBrowser->setText("You are about to bet 0.1 Chips on Tie\n\nPayout is 8:1\n\nClick Ok to confirm this bet");
}


void confirmmenu::getConfirmText()
{
    ui->confirmTextBrowser->setText("You are about to trade 0.5 Dero for 4.5 Chips\n\nClick Ok to confirm this bet");
}


void confirmmenu::tradeConfirmText()
{
    ui->confirmTextBrowser->setText("You are about to trade 1 Chip for 0.111 Dero\n\nClick Ok to confirm this bet");
}
