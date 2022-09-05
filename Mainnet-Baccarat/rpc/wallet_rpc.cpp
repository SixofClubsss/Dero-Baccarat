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
#include "dialog.h"
#include "rpc.h"

///using std::string;
string rpc::rpcLogin;
QString readout::deroAmount;
QString readout::chipAmount;
QString readout::tieAmount;
QString readout::bankerAmount;
QString readout::playerAmount;
QString readout::deroConverted;
QString readout::chipsConverted;
QString rpc::contractAddress;
QString rpc::tokenAddress;
QString rpc::txidCheck;
int rpc::thisHand;
bool rpc::daemonConnected;
bool rpc::walletConnected;


void MainWindow::loginInfo()   /// Used to store wallet login info for all wallet functions
{
    QString userpassInfo = ui->userpassInput->text();
    string userpassStr = userpassInfo.toStdString();
    rpc::rpcLogin = userpassStr;
}


void MainWindow::readoutConfirm()   /// Used to confirm bet
{
    QString deroInfo = QString::number(ui->getChipsAmount->value());
    QString tradeChipsInfo = QString::number(ui->tradeChipsAmount->value());
    QString tieChipsInfo = QString::number(ui->tieBetAmount->value());
    QString bankerChipsInfo = QString::number(ui->bankerBetAmount->value());
    QString playerChipsInfo = QString::number(ui->playerBetAmount->value());
    QString convertMultiply = QString::number(ui->getChipsAmount->value()*333);
    double getDecimal = ui->tradeChipsAmount->value();
    double showDecimal = getDecimal/333;
    QString convertDivide =  QString::number(showDecimal);

    readout::deroAmount = deroInfo;
    readout::chipAmount = tradeChipsInfo;
    readout::tieAmount = tieChipsInfo;
    readout::bankerAmount = bankerChipsInfo;
    readout::playerAmount = playerChipsInfo;
    readout::deroConverted = convertMultiply;
    readout::chipsConverted = convertDivide;

}


int MainWindow::checkWallet()  /// Echo blockchain to confirm wallet is connected
{
    CURL *curlWalletCheck;      /// Set up cUrl
    CURLcode res;
    string readBuffer;

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\":\"1\",\"method\":\"Echo\", \"params\":[\"Hello\", \"World\", \"!\"]}";
    char error[CURL_ERROR_SIZE];
    rpc::walletAddress = ui->walletRPCinput->text()+"/json_rpc";

    string pStr = rpc::walletAddress.toStdString();
    const char *pCh = pStr.c_str ();

    loginInfo();            /// Get login info
    const char *loginCh = rpc::rpcLogin.c_str();

    curlWalletCheck = curl_easy_init();

    if(curlWalletCheck) {
        struct curl_slist *headers = NULL;
        /// Add request headers
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        /// cUrl options
        curl_easy_setopt(curlWalletCheck, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curlWalletCheck, CURLOPT_URL, pCh);
        curl_easy_setopt(curlWalletCheck, CURLOPT_VERBOSE, 0L);
        curl_easy_setopt(curlWalletCheck, CURLOPT_ERRORBUFFER, error);
        curl_easy_setopt(curlWalletCheck, CURLOPT_CONNECTTIMEOUT, 9L);
        curl_easy_setopt(curlWalletCheck, CURLOPT_USERPWD, loginCh);
        curl_easy_setopt(curlWalletCheck, CURLOPT_POSTFIELDS, postthis);
        curl_easy_setopt(curlWalletCheck, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
        curl_easy_setopt(curlWalletCheck, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curlWalletCheck, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curlWalletCheck);
        curl_easy_cleanup(curlWalletCheck);           ///Preform cUrl and clean up

        QByteArray br = readBuffer.c_str();           /// Get cUrl results into QByteArray
        QJsonDocument cbDoc = QJsonDocument::fromJson(br);
        QJsonObject cbObj = cbDoc.object();
        QJsonValue okCheck = cbObj["result"];

        if(okCheck == "WALLET Hello World !"){

            ui->walletConnectedBox->setChecked(true);      /// Wallet connected
            ui->textBrowser->setText("Wallet Connected");
            rpc::walletConnected = true;
            buttonControl(true);
        }else {
            ui->walletConnectedBox->setChecked(false);
            ui->textBrowser->setText("Wallet Not Connected");   /// Wallet NOT connected
            rpc::walletAddress = "null";

            if(rpc::walletConnected == true){
                rpc::walletConnected = false;
                buttonControl(false);
            }

        }

    }
    return 0;
}


int MainWindow::getChips()      /// Trade Dero for dReams token (Only dReams are accepted for bets)
{
    CURL *curlGetChips;
    CURLcode res;
    string getChipsReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString dAmount = QString::number(ui->getChipsAmount->value()*100000, 'g', 10);
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\""+rpc::contractAddress+"\", \"sc_dero_deposit\":"+dAmount+", \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"IssueChips\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::walletAddress.toStdString();
    const char *gcCh = pStr.c_str ();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlGetChips = curl_easy_init();

    if(curlGetChips) {
        struct curl_slist *headers = NULL;

        /// Add request headers
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        /// cUrl options
        curl_easy_setopt(curlGetChips, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curlGetChips, CURLOPT_URL, gcCh);
        curl_easy_setopt(curlGetChips, CURLOPT_VERBOSE, 0L);
        curl_easy_setopt(curlGetChips, CURLOPT_ERRORBUFFER, error);
        curl_easy_setopt(curlGetChips, CURLOPT_CONNECTTIMEOUT, 9L);
        curl_easy_setopt(curlGetChips, CURLOPT_USERPWD, loginCh);
        curl_easy_setopt(curlGetChips, CURLOPT_POSTFIELDS, postthis);
        curl_easy_setopt(curlGetChips, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
        curl_easy_setopt(curlGetChips, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curlGetChips, CURLOPT_WRITEDATA, &getChipsReadBuffer);

        res = curl_easy_perform(curlGetChips);
        curl_easy_cleanup(curlGetChips);

        QByteArray br = getChipsReadBuffer.c_str();
        QJsonDocument cbDoc = QJsonDocument::fromJson(br);
        QJsonObject cbObj = cbDoc.object();
        QJsonObject cbResults = cbObj["result"].toObject();
        QJsonValue getChipsTxid = cbResults.value("txid");

        if(getChipsTxid.isString()){
            ui->textBrowser->setText("Get dReams TXID: "+getChipsTxid.toString());  /// Displays TXID and adds TXID to session log
            ui->logTextBrowser->append("TXID: "+getChipsTxid.toString()+"\n");
        }else {
            ui->textBrowser->setText("Error No Get dReams TXID");      /// No TXID was recieved
        }

    }
    return 0;
}


int MainWindow::tradeChips()        /// Trade dReams for Dero
{
    CURL *curlTradeChips;
    CURLcode res;
    string tradeChipsReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString cAmount = QString::number(ui->tradeChipsAmount->value()*100000);
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\":[{\"scid\":\""+rpc::tokenAddress+"\", \"burn\":"+cAmount+"}] ,\"scid\":\""+rpc::contractAddress+"\", \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"ConvertChips\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::walletAddress.toStdString();
    const char *tcCh = pStr.c_str ();

    const char *loginCh = rpc::rpcLogin.c_str ();

    curlTradeChips = curl_easy_init();

    if(curlTradeChips) {
        struct curl_slist *headers = NULL;

        /// Add request headers
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        /// cUrl options
        curl_easy_setopt(curlTradeChips, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curlTradeChips, CURLOPT_URL, tcCh);
        curl_easy_setopt(curlTradeChips, CURLOPT_VERBOSE, 0L);
        curl_easy_setopt(curlTradeChips, CURLOPT_ERRORBUFFER, error);
        curl_easy_setopt(curlTradeChips, CURLOPT_CONNECTTIMEOUT, 9L);
        curl_easy_setopt(curlTradeChips, CURLOPT_USERPWD, loginCh);
        curl_easy_setopt(curlTradeChips, CURLOPT_POSTFIELDS, postthis);
        curl_easy_setopt(curlTradeChips, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
        curl_easy_setopt(curlTradeChips, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curlTradeChips, CURLOPT_WRITEDATA, &tradeChipsReadBuffer);

        res = curl_easy_perform(curlTradeChips);
        curl_easy_cleanup(curlTradeChips);

        QByteArray br = tradeChipsReadBuffer.c_str();
        QJsonDocument cbDoc = QJsonDocument::fromJson(br);
        QJsonObject cbObj = cbDoc.object();
        QJsonObject cbResults = cbObj["result"].toObject();
        QJsonValue tradeChipsTxid = cbResults.value("txid");

        if(tradeChipsTxid.isString()){
            ui->textBrowser->setText("Trade dReams TXID: "+tradeChipsTxid.toString());
            ui->logTextBrowser->append("TXID: "+tradeChipsTxid.toString()+"\n");
        }else {
            ui->textBrowser->setText("Error No Trade dReams TXID");
        }

    }
    return 0;
}


int MainWindow::playerBet()     /// Bet on player
{
    CURL *curlPlayer;
    CURLcode res;
    string pReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString cAmount = QString::number(ui->playerBetAmount->value()*100000);
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\": [{\"scid\":\""+rpc::tokenAddress+"\", \"burn\":"+cAmount+"}],\"scid\":\""+rpc::contractAddress+"\",\"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"PlayBaccarat\"},{\"name\":\"betOn\",\"datatype\":\"S\",\"value\":\"player\" }]}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::walletAddress.toStdString();
    const char *pCh = pStr.c_str ();

    const char *loginCh = rpc::rpcLogin.c_str ();

    curlPlayer = curl_easy_init();

    if(curlPlayer) {
        struct curl_slist *headers = NULL;

        /// Add request headers
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        /// cUrl options
        curl_easy_setopt(curlPlayer, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curlPlayer, CURLOPT_URL, pCh);
        curl_easy_setopt(curlPlayer, CURLOPT_VERBOSE, 0L);
        curl_easy_setopt(curlPlayer, CURLOPT_ERRORBUFFER, error);
        curl_easy_setopt(curlPlayer, CURLOPT_CONNECTTIMEOUT, 9L);
        curl_easy_setopt(curlPlayer, CURLOPT_USERPWD, loginCh);
        curl_easy_setopt(curlPlayer, CURLOPT_POSTFIELDS, postthis);
        curl_easy_setopt(curlPlayer, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
        curl_easy_setopt(curlPlayer, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curlPlayer, CURLOPT_WRITEDATA, &pReadBuffer);

        res = curl_easy_perform(curlPlayer);
        curl_easy_cleanup(curlPlayer);

        QByteArray br = pReadBuffer.c_str();
        QJsonDocument cbDoc = QJsonDocument::fromJson(br);
        QJsonObject cbObj = cbDoc.object();
        QJsonObject cbResults = cbObj["result"].toObject();
        QJsonValue txid = cbResults.value("txid");

        if(txid.isString()){
            rpc::txidCheck = txid.toString();
            rpc::thisHand = ui->dsbTotalHandsPlayed->value();
            ui->textBrowser->setText("Your Hand TXID: "+txid.toString());
            ui->textBrowser->append("\nWait for Block");
            ui->logTextBrowser->append("TXID: "+txid.toString()+"\n");
        }else {
            ui->textBrowser->setText("Error No Hand TXID");
        }

    }
    return 0;
}


int MainWindow::bankerBet()     /// Bet on banker
{
    CURL *curlBanker;
    CURLcode res;
    string bReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString cAmount = QString::number(ui->bankerBetAmount->value()*100000);
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\": [{\"scid\":\""+rpc::tokenAddress+"\", \"burn\":"+cAmount+"}],\"scid\":\""+rpc::contractAddress+"\",\"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"PlayBaccarat\"},{\"name\":\"betOn\",\"datatype\":\"S\",\"value\":\"banker\" }]}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::walletAddress.toStdString();
    const char *pCh = pStr.c_str ();

    const char *loginCh = rpc::rpcLogin.c_str ();

    curlBanker = curl_easy_init();

    if(curlBanker) {
        struct curl_slist *headers = NULL;

        /// Add request headers
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        /// cUrl options
        curl_easy_setopt(curlBanker, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curlBanker, CURLOPT_URL, pCh);
        curl_easy_setopt(curlBanker, CURLOPT_VERBOSE, 0L);
        curl_easy_setopt(curlBanker, CURLOPT_ERRORBUFFER, error);
        curl_easy_setopt(curlBanker, CURLOPT_CONNECTTIMEOUT, 9L);
        curl_easy_setopt(curlBanker, CURLOPT_USERPWD, loginCh);
        curl_easy_setopt(curlBanker, CURLOPT_POSTFIELDS, postthis);
        curl_easy_setopt(curlBanker, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
        curl_easy_setopt(curlBanker, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curlBanker, CURLOPT_WRITEDATA, &bReadBuffer);

        res = curl_easy_perform(curlBanker);
        curl_easy_cleanup(curlBanker);

        QByteArray br = bReadBuffer.c_str();
        QJsonDocument cbDoc = QJsonDocument::fromJson(br);
        QJsonObject cbObj = cbDoc.object();
        QJsonObject cbResults = cbObj["result"].toObject();
        QJsonValue txid = cbResults.value("txid");

        if(txid.isString()){
            rpc::txidCheck = txid.toString();
            rpc::thisHand = ui->dsbTotalHandsPlayed->value();
            ui->textBrowser->setText("Your Hand TXID: "+txid.toString());
            ui->textBrowser->append("\nWait for Block");
            ui->logTextBrowser->append("TXID: "+txid.toString()+"\n");
        }else {
            ui->textBrowser->setText("Error No Hand TXID");
        }

    }
    return 0;
}


int MainWindow::tieBet()            /// Bet on tie
{
    CURL *curlTie;
    CURLcode res;
    string tReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString cAmount = QString::number(ui->tieBetAmount->value()*100000);
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\": [{\"scid\":\""+rpc::tokenAddress+"\", \"burn\":"+cAmount+"}],\"scid\":\""+rpc::contractAddress+"\",\"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"PlayBaccarat\"},{\"name\":\"betOn\",\"datatype\":\"S\",\"value\":\"tie\" }]}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::walletAddress.toStdString();
    const char *tCh = pStr.c_str ();

    const char *loginCh = rpc::rpcLogin.c_str ();

    curlTie = curl_easy_init();

    if(curlTie) {
        struct curl_slist *headers = NULL;

        /// Add request headers
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        /// cUrl options
        curl_easy_setopt(curlTie, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curlTie, CURLOPT_URL, tCh);
        curl_easy_setopt(curlTie, CURLOPT_VERBOSE, 0L);
        curl_easy_setopt(curlTie, CURLOPT_ERRORBUFFER, error);
        curl_easy_setopt(curlTie, CURLOPT_CONNECTTIMEOUT, 9L);
        curl_easy_setopt(curlTie, CURLOPT_USERPWD, loginCh);
        curl_easy_setopt(curlTie, CURLOPT_POSTFIELDS, postthis);
        curl_easy_setopt(curlTie, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
        curl_easy_setopt(curlTie, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curlTie, CURLOPT_WRITEDATA, &tReadBuffer);

        res = curl_easy_perform(curlTie);
        curl_easy_cleanup(curlTie);

        QByteArray br = tReadBuffer.c_str();
        QJsonDocument cbDoc = QJsonDocument::fromJson(br);
        QJsonObject cbObj = cbDoc.object();
        QJsonObject cbResults = cbObj["result"].toObject();
        QJsonValue txid = cbResults.value("txid");

        if(txid.isString()){
            rpc::txidCheck = txid.toString();
            rpc::thisHand = ui->dsbTotalHandsPlayed->value();
            ui->textBrowser->setText("Your Hand TXID: "+txid.toString());
            ui->textBrowser->append("\nWait for Block");
            ui->logTextBrowser->append("TXID: "+txid.toString()+"\n");
        }else {
            ui->textBrowser->setText("Error No Hand TXID");
        }

    }
    return 0;
}
