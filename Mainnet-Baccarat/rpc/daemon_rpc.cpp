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


using std::string;


int rpc::getDeroBalance()  /// Gets players dero balance
{
    CURL *curlBalanceCheck;
    CURLcode res;
    string balanceReadBuffer;
    char error[CURL_ERROR_SIZE];

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\": \"1\",\"method\": \"GetBalance\"}";

    string pStr = rpc::walletAddress.toStdString();
    const char *pCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlBalanceCheck = curl_easy_init();

    if(curlBalanceCheck) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlBalanceCheck, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlBalanceCheck, CURLOPT_URL, pCh);
      curl_easy_setopt(curlBalanceCheck, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlBalanceCheck, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlBalanceCheck, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlBalanceCheck, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlBalanceCheck, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlBalanceCheck, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlBalanceCheck, CURLOPT_WRITEDATA, &balanceReadBuffer);
      res = curl_easy_perform(curlBalanceCheck);
      curl_easy_cleanup(curlBalanceCheck);

      QByteArray br = balanceReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue Balance_jv = cbResults.value("balance");

      rpc::deroBalance = Balance_jv.toDouble();

    }
    return 0;
}


int rpc::getdReamBalance()  /// Gets players dReam balance
{
    CURL *curldReamBalanceCheck;
    CURLcode res;
    string balanceReadBuffer;
    char error[CURL_ERROR_SIZE];

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\": \"1\",\"method\": \"GetBalance\", \"params\": {\"scid\": \"ad2e7b37c380cc1aed3a6b27224ddfc92a2d15962ca1f4d35e530dba0f9575a9\"}}";

    string pStr = rpc::walletAddress.toStdString();
    const char *pCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

    curldReamBalanceCheck = curl_easy_init();

    if(curldReamBalanceCheck) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curldReamBalanceCheck, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curldReamBalanceCheck, CURLOPT_URL, pCh);
      curl_easy_setopt(curldReamBalanceCheck, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curldReamBalanceCheck, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curldReamBalanceCheck, CURLOPT_CONNECTTIMEOUT, 9L);
      curl_easy_setopt(curldReamBalanceCheck, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curldReamBalanceCheck, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curldReamBalanceCheck, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curldReamBalanceCheck, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curldReamBalanceCheck, CURLOPT_WRITEDATA, &balanceReadBuffer);
      res = curl_easy_perform(curldReamBalanceCheck);
      curl_easy_cleanup(curldReamBalanceCheck);

      QByteArray dbr = balanceReadBuffer.c_str();
      QJsonDocument cbdDoc = QJsonDocument::fromJson(dbr);
      QJsonObject cbdObj = cbdDoc.object();
      QJsonObject cbdResults = cbdObj["result"].toObject();
      QJsonValue dBalance_jv = cbdResults.value("balance");

      rpc::dReamBalance = dBalance_jv.toDouble();

    }
    return 0;
}


int rpc::getHeight()  /// Gets current block height
{
    CURL *curlHeightCheck;
    CURLcode res;
    string heightReadBuffer;
    char error[CURL_ERROR_SIZE];

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\": \"1\",\"method\": \"DERO.GetHeight\"}";

    string dStr = rpc::daemonAddress.toStdString();
    const char *fhCh = dStr.c_str();

    curlHeightCheck = curl_easy_init();

    if(curlHeightCheck) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlHeightCheck, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlHeightCheck, CURLOPT_URL, fhCh);
      curl_easy_setopt(curlHeightCheck, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlHeightCheck, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlHeightCheck, CURLOPT_CONNECTTIMEOUT, 9L);
      /// curl_easy_setopt(curlHeightCheck, CURLOPT_SSL_VERIFYPEER, 0);   *Remove comment for windows SSL disable*
      curl_easy_setopt(curlHeightCheck, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlHeightCheck, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlHeightCheck, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlHeightCheck, CURLOPT_WRITEDATA, &heightReadBuffer);
      res = curl_easy_perform(curlHeightCheck);
      curl_easy_cleanup(curlHeightCheck);

      QByteArray br = heightReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue Height_jv = cbResults.value("height");

      rpc::blockHeight = Height_jv.toInt();

    }
    return 0;
}


int rpc::fetchScData()       /// Get SC variables
{
    CURL *curlFetch;                /// Set up cUrl
    CURLcode res;
    string fetchReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\""+rpc::contractAddress+"\" , \"ringsize\":2 , \"code\":false , \"variables\":true}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string dStr = rpc::daemonAddress.toStdString();
    const char *dCh = dStr.c_str();

    curlFetch = curl_easy_init();

    if(curlFetch) {
      struct curl_slist *headers = NULL;

      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlFetch, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlFetch, CURLOPT_URL, dCh);
      curl_easy_setopt(curlFetch, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlFetch, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlFetch, CURLOPT_CONNECTTIMEOUT, 9L);
      /// curl_easy_setopt(curlFetch, CURLOPT_SSL_VERIFYPEER, 0);   *Remove comment for widnows SSL disable*
      curl_easy_setopt(curlFetch, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlFetch, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlFetch, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlFetch, CURLOPT_WRITEDATA, &fetchReadBuffer);

      res = curl_easy_perform(curlFetch);   /// Preform cUrl and clean up
      curl_easy_cleanup(curlFetch);

      std::cout << fetchReadBuffer << std::endl;

      QByteArray br = fetchReadBuffer.c_str();      /// Get cUrl results into QByteArray
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonObject cbStringKeys = cbResults["stringkeys"].toObject();
      QJsonValue TotalHands_jv = cbStringKeys.value("TotalHandsPlayed:");
      QJsonValue PlayerWins_jv = cbStringKeys.value("Player Wins:");
      QJsonValue BankerWins_jv = cbStringKeys.value("Banker Wins:");
      QJsonValue TotalTies_jv = cbStringKeys.value("Ties:");

      rpc::totalHands = TotalHands_jv.toDouble();
      rpc::playerWins = PlayerWins_jv.toInt();
      rpc::bankerWins = BankerWins_jv.toInt();
      rpc::totalTies = TotalTies_jv.toInt();

      if(rpc::foundHand == false){
        int i = TotalHands_jv.toInt();
        do{
          QString handId = QString::number(i-6);

          QJsonValue handTXID = cbStringKeys.value(handId.toUtf8()+"-Hand#TXID:");
          QJsonValue playerTotal = cbStringKeys.value(handId.toUtf8()+"-Player total:");
          QJsonValue playerX = cbStringKeys.value(handId.toUtf8()+"-Player x:");
          QJsonValue playerY = cbStringKeys.value(handId.toUtf8()+"-Player y:");
          QJsonValue playerZ = cbStringKeys.value(handId.toUtf8()+"-Player z:");

          QJsonValue bankerTotal = cbStringKeys.value(handId.toUtf8()+"-Banker total:");
          QJsonValue bankerX = cbStringKeys.value(handId.toUtf8()+"-Banker x:");
          QJsonValue bankerY = cbStringKeys.value(handId.toUtf8()+"-Banker y:");
          QJsonValue bankerZ = cbStringKeys.value(handId.toUtf8()+"-Banker z:");
          i++;
          if(rpc::txidCheck == handTXID.toString()){
             rpc::foundHandTXID = handTXID.toString();
             rpc::foundPlayerTotal = playerTotal.toDouble();
             rpc::foundPlayerX = playerX.toInt();
             rpc::foundPlayerY = playerY.toInt();
             rpc::foundPlayerZ = playerZ.toInt();
             rpc::foundBankerTotal = bankerTotal.toDouble();
             rpc::foundBankerX = bankerX.toInt();
             rpc::foundBankerY = bankerY.toInt();
             rpc::foundBankerZ = bankerZ.toInt();
             rpc::foundHand = true;
             break;
          }

        }while(i < TotalHands_jv.toInt()+26);

      }else {
          rpc::foundHand = false;
      }

    }
    return 0;
}


int MainWindow::checkDaemon()       /// Check connection to daemon
{
    CURL *curlDaemonCheck;
    CURLcode res;
    string readBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\""+rpc::contractAddress+"\" , \"ringsize\":2 , \"code\":false , \"variables\":false}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    rpc::daemonAddress =  ui->daemonRPCinput->text()+"/json_rpc";
    string dStr = rpc::daemonAddress.toStdString();
    const char *dCh = dStr.c_str();

    curlDaemonCheck = curl_easy_init();

    if(curlDaemonCheck) {
      struct curl_slist *headers = NULL;

      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlDaemonCheck, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlDaemonCheck, CURLOPT_URL, dCh);
      curl_easy_setopt(curlDaemonCheck, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlDaemonCheck, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlDaemonCheck, CURLOPT_CONNECTTIMEOUT, 9L);
      /// curl_easy_setopt(curlDaemonCheck, CURLOPT_SSL_VERIFYPEER, 0);   *Remove comment for widnows SSL disable*
      curl_easy_setopt(curlDaemonCheck, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlDaemonCheck, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlDaemonCheck, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlDaemonCheck, CURLOPT_WRITEDATA, &readBuffer);

      res = curl_easy_perform(curlDaemonCheck);
      curl_easy_cleanup(curlDaemonCheck);

      QByteArray br = readBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue okCheck = cbResults["status"];

      std::cout << readBuffer << std::endl;

      if(okCheck == "OK"){
          rpc::daemonConnected = true;
          ui->daemonConnectedBox->setChecked(true);
          ui->textBrowser->setText("Daemon Connected");
          std::cout << "Daemon Connected" << std::endl;     /// Connected message
      }else {

          ui->daemonConnectedBox->setChecked(false);
          ui->textBrowser->setText("Daemon Not Connected");
          std::cout << "Daemon Not Connected" << std::endl;  /// Not connected
      }

    }
    return 0;
}


int MainWindow::searchHandData()   /// Search hands stored on SC
{
    CURL *curlSearchHandData;
    CURLcode res;
    string readBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\""+rpc::contractAddress+"\" , \"ringsize\":2 , \"code\":false , \"variables\":true}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string dStr = rpc::daemonAddress.toStdString();
    const char *dCh = dStr.c_str();

    curlSearchHandData = curl_easy_init();

    if(curlSearchHandData) {
      struct curl_slist *headers = NULL;

      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlSearchHandData, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlSearchHandData, CURLOPT_URL, dCh);
      curl_easy_setopt(curlSearchHandData, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlSearchHandData, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlSearchHandData, CURLOPT_CONNECTTIMEOUT, 9L);
      curl_easy_setopt(curlSearchHandData, CURLOPT_POSTFIELDS, postthis);
      /// curl_easy_setopt(curlSearchHandData, CURLOPT_SSL_VERIFYPEER, 0);   *Remove comment for widnows SSL disable*
      curl_easy_setopt(curlSearchHandData, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlSearchHandData, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlSearchHandData, CURLOPT_WRITEDATA, &readBuffer);

      res = curl_easy_perform(curlSearchHandData);
      curl_easy_cleanup(curlSearchHandData);

      QByteArray br = readBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonObject cbStringKeys = cbResults["stringkeys"].toObject();

      QString searchId = QString::number(ui->searchDoubleSpinBox->value());

      QJsonValue handTXID = cbStringKeys.value(searchId.toUtf8()+"-Hand#TXID:");
      QJsonValue playerTotal = cbStringKeys.value(searchId.toUtf8()+"-Player total:");
      QJsonValue playerX = cbStringKeys.value(searchId.toUtf8()+"-Player x:");
      QJsonValue playerY = cbStringKeys.value(searchId.toUtf8()+"-Player y:");
      QJsonValue playerZ = cbStringKeys.value(searchId.toUtf8()+"-Player z:");

      QJsonValue bankerTotal = cbStringKeys.value(searchId.toUtf8()+"-Banker total:");
      QJsonValue bankerX = cbStringKeys.value(searchId.toUtf8()+"-Banker x:");
      QJsonValue bankerY = cbStringKeys.value(searchId.toUtf8()+"-Banker y:");
      QJsonValue bankerZ = cbStringKeys.value(searchId.toUtf8()+"-Banker z:");

      ui->playerTotalSpinBox->setValue(playerTotal.toDouble());
      ui->playerXCardLabel->setPixmap(displayPlayerCards(playerX.toInt()));
      ui->playerYCardLabel->setPixmap(displayPlayerCards(playerY.toInt()));
      ui->playerZCardLabel->setPixmap(displayDrawPlayerCard(playerZ.toInt()));

      ui->bankerTotalSpinBox->setValue(bankerTotal.toDouble());
      ui->bankerXCardLabel->setPixmap(displayBankerCards(bankerX.toInt()));
      ui->bankerYCardLabel->setPixmap(displayBankerCards(bankerY.toInt()));
      ui->bankerZCardLabel->setPixmap(displayDrawBankerCard(bankerZ.toInt()));

      if(handTXID.isUndefined()){
          ui->textBrowser->setText("Error Hand Number Does Not Exist");
          blankCards();

      }else {
          ui->textBrowser->setText("Displaying hand TXID: "+handTXID.toString());
          if(playerTotal.toInt() > bankerTotal.toInt()){
               ui->textBrowser->append("\nPlayer Wins");
               ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: rgb(79, 186, 196, 210); background-color: rgb(79, 186, 196, 21); };");
          }

          if(bankerTotal.toInt() > playerTotal.toInt()){
               ui->textBrowser->append("\nBanker Wins");
               ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: rgb(79, 186, 196, 210); background-color: rgb(79, 186, 196, 21); };");
          }

          if(bankerTotal.toInt() == playerTotal.toInt()){
               ui->textBrowser->append("\nTie");
               ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: rgb(56, 47, 165, 210); background-color: rgb(28, 31, 43, 0); };");
               ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: rgb(56, 47, 165, 210); background-color: rgb(28, 31, 43, 0); };");
          }
      }

    }
    return 0;

}


void MainWindow::blankCards()  /// Null display
{
    ui->playerTotalSpinBox->setValue(0);

    ui->playerXCardLabel->setPixmap(QPixmap(":/CardBack"));
    ui->playerYCardLabel->setPixmap(QPixmap(":/CardBack"));
    ui->playerZCardLabel->setPixmap(QPixmap(":/CardBack"));

    ui->bankerTotalSpinBox->setValue(0);
    ui->bankerXCardLabel->setPixmap(QPixmap(":/CardBack"));
    ui->bankerYCardLabel->setPixmap(QPixmap(":/CardBack"));
    ui->bankerZCardLabel->setPixmap(QPixmap(":/CardBack"));
}


QPixmap MainWindow::displayPlayerCards(int card) /// Card display
{
    QPixmap pcardEquiv;
        switch(card){
        case 0: pcardEquiv = QPixmap(":/Card0"); break;
        case 1: pcardEquiv = QPixmap(":/Card1"); break;
        case 2: pcardEquiv = QPixmap(":/Card2"); break;
        case 3: pcardEquiv = QPixmap(":/Card3"); break;
        case 4: pcardEquiv = QPixmap(":/Card4"); break;
        case 5: pcardEquiv = QPixmap(":/Card5"); break;
        case 6: pcardEquiv = QPixmap(":/Card6"); break;
        case 7: pcardEquiv = QPixmap(":/Card7"); break;
        case 8: pcardEquiv = QPixmap(":/Card8"); break;
        case 9: pcardEquiv = QPixmap(":/Card9"); break;
        case 10: pcardEquiv = QPixmap(":/Card0"); break;
        case 11: pcardEquiv = QPixmap(":/Card0"); break;
        case 12: pcardEquiv = QPixmap(":/Card0"); break;
        case 13: pcardEquiv = QPixmap(":/Card0"); break;
        }

    return pcardEquiv;
}


QPixmap MainWindow::displayBankerCards(int card)
{
    QPixmap cardEquiv;
        switch(card){
        case 0: cardEquiv = QPixmap(":/Card0"); break;
        case 1: cardEquiv = QPixmap(":/Card1"); break;
        case 2: cardEquiv = QPixmap(":/Card2"); break;
        case 3: cardEquiv = QPixmap(":/Card3"); break;
        case 4: cardEquiv = QPixmap(":/Card4"); break;
        case 5: cardEquiv = QPixmap(":/Card5"); break;
        case 6: cardEquiv = QPixmap(":/Card6"); break;
        case 7: cardEquiv = QPixmap(":/Card7"); break;
        case 8: cardEquiv = QPixmap(":/Card8"); break;
        case 9: cardEquiv = QPixmap(":/Card9"); break;
        case 10: cardEquiv = QPixmap(":/Card0"); break;
        case 11: cardEquiv = QPixmap(":/Card0"); break;
        case 12: cardEquiv = QPixmap(":/Card0"); break;
        case 13: cardEquiv = QPixmap(":/Card0"); break;
        }

    return cardEquiv;
}


QPixmap MainWindow::displayDrawPlayerCard(int card)
{
    QPixmap pcardEquiv;
        switch(card){
        case 0: pcardEquiv = QPixmap(":/CardBack"); break;
        case 1: pcardEquiv = QPixmap(":/Card1"); break;
        case 2: pcardEquiv = QPixmap(":/Card2"); break;
        case 3: pcardEquiv = QPixmap(":/Card3"); break;
        case 4: pcardEquiv = QPixmap(":/Card4"); break;
        case 5: pcardEquiv = QPixmap(":/Card5"); break;
        case 6: pcardEquiv = QPixmap(":/Card6"); break;
        case 7: pcardEquiv = QPixmap(":/Card7"); break;
        case 8: pcardEquiv = QPixmap(":/Card8"); break;
        case 9: pcardEquiv = QPixmap(":/Card9"); break;
        case 10: pcardEquiv = QPixmap(":/Card0"); break;
        case 11: pcardEquiv = QPixmap(":/Card0"); break;
        case 12: pcardEquiv = QPixmap(":/Card0"); break;
        case 13: pcardEquiv = QPixmap(":/Card0"); break;
        }

    return pcardEquiv;
}


QPixmap MainWindow::displayDrawBankerCard(int card)
{
    QPixmap cardEquiv;
        switch(card){
        case 0: cardEquiv = QPixmap(":/CardBack"); break;
        case 1: cardEquiv = QPixmap(":/Card1"); break;
        case 2: cardEquiv = QPixmap(":/Card2"); break;
        case 3: cardEquiv = QPixmap(":/Card3"); break;
        case 4: cardEquiv = QPixmap(":/Card4"); break;
        case 5: cardEquiv = QPixmap(":/Card5"); break;
        case 6: cardEquiv = QPixmap(":/Card6"); break;
        case 7: cardEquiv = QPixmap(":/Card7"); break;
        case 8: cardEquiv = QPixmap(":/Card8"); break;
        case 9: cardEquiv = QPixmap(":/Card9"); break;
        case 10: cardEquiv = QPixmap(":/Card0"); break;
        case 11: cardEquiv = QPixmap(":/Card0"); break;
        case 12: cardEquiv = QPixmap(":/Card0"); break;
        case 13: cardEquiv = QPixmap(":/Card0"); break;
        }

    return cardEquiv;
}
