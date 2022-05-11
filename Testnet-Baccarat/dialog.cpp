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
    ui->confirmTextBrowser->setText("You are about to bet "+readout::playerAmount+" Chips on Player\n\nPayout is 1:1\n\nClick Ok to confirm this bet");
}

void Dialog::bankerConfirmText()
{
    ui->confirmTextBrowser->setText("You are about to bet 0 "+readout::bankerAmount+" Chips on Banker\n\nPayout is 0.95:1\n(House takes 5% commission)\n\nClick Ok to confirm this bet");
}

void Dialog::tieConfirmText()
{
    ui->confirmTextBrowser->setText("You are about to bet "+readout::tieAmount+" Chips on Tie\n\nPayout is 8:1\n\nClick Ok to confirm this bet");
}


void Dialog::getConfirmText()
{
    ui->confirmTextBrowser->setText("You are about to trade "+readout::deroAmount+" Dero for "+readout::deroConverted+" Chips\n\nClick Ok to confirm this bet");
}


void Dialog::tradeConfirmText()
{
    ui->confirmTextBrowser->setText("You are about to trade "+readout::chipAmount+" Chips for "+readout::chipsConverted+" Dero\n\nClick Ok to confirm this bet");
}
