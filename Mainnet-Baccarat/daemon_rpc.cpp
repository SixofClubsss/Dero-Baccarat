#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "rpc.h"

using std::string;


void MainWindow::delay()            /// Delay for block time
{
    QTime dieTime= QTime::currentTime().addSecs(30);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


int MainWindow::fetchScData(void)       /// Get SC variables
{
    CURL *curlFetch;                /// Set up cUrl
    CURLcode res;
    string fetchReadBuffer;

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\"da78f97e1aec885b8a3f75b1af2892dcd0a13342b645320e46cf0edf8c17478b\" , \"ringsize\":2 , \"code\":false , \"variables\":true}}";
    char error[CURL_ERROR_SIZE];
    QString daemonAddress =  ui->daemonRPCinput->text()+"/json_rpc";
    string dStr = daemonAddress.toStdString();
    const char *dCh = dStr.c_str ();

    loginInfo();        /// Get logn info
    const char *loginCh = rpc::rpcLogin.c_str ();

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
      curl_easy_setopt(curlFetch, CURLOPT_USERPWD, loginCh);
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
      QJsonValue totalHands = cbStringKeys.value("TotalHandsPlayed:");
      QJsonValue playerWins = cbStringKeys.value("Player Wins:");
      QJsonValue bankerWins = cbStringKeys.value("Banker Wins:");
      QJsonValue totalTies = cbStringKeys.value("Ties:");
      QJsonValue playing = cbStringKeys.value("At Table:");

      ui->dsbTotalHandsPlayed->setValue(totalHands.toDouble()); /// Updates total hands played display
      ui->pWinsSpinBox->setValue(playerWins.toInt());
      ui->bWinsSpinBox->setValue(bankerWins.toInt());
      ui->tWinsSpinBox->setValue(totalTies.toInt());
      ui->atTableSpinBox->setValue(playing.toInt());

    }
    return 0;
}


int MainWindow::checkDaemon(void)       /// Check connection to daemon
{
    CURL *curlDaemonCheck;
    CURLcode res;
    string readBuffer;

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\"da78f97e1aec885b8a3f75b1af2892dcd0a13342b645320e46cf0edf8c17478b\" , \"ringsize\":2 , \"code\":false , \"variables\":false}}";
    char error[CURL_ERROR_SIZE];
    QString daemonAddress =  ui->daemonRPCinput->text()+"/json_rpc";
    string dStr = daemonAddress.toStdString();
    const char *dCh = dStr.c_str ();

    loginInfo();
    const char *loginCh = rpc::rpcLogin.c_str ();

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
      curl_easy_setopt(curlDaemonCheck, CURLOPT_USERPWD, loginCh);
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

      if(okCheck == "OK")
      {
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


int MainWindow::fetchHandData(void)
{
    CURL *curlHandData;
    CURLcode res;
    string readBuffer;

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\"da78f97e1aec885b8a3f75b1af2892dcd0a13342b645320e46cf0edf8c17478b\" , \"ringsize\":2 , \"code\":false , \"variables\":true}}";
    char error[CURL_ERROR_SIZE];
    QString daemonAddress =  ui->daemonRPCinput->text()+"/json_rpc";
    string dStr = daemonAddress.toStdString();
    const char *dCh = dStr.c_str ();

    loginInfo();
    const char *loginCh = rpc::rpcLogin.c_str ();


    curlHandData = curl_easy_init();
    if(curlHandData) {
      struct curl_slist *headers = NULL;

      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlHandData, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlHandData, CURLOPT_URL, dCh);
      curl_easy_setopt(curlHandData, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlHandData, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlHandData, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlHandData, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlHandData, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlHandData, CURLOPT_WRITEDATA, &readBuffer);

      res = curl_easy_perform(curlHandData);
      curl_easy_cleanup(curlHandData);

      QByteArray br = readBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonObject cbStringKeys = cbResults["stringkeys"].toObject();

      QString handId = QString::number(rpc::thisHand);

      QJsonValue handTXID = cbStringKeys.value(handId.toUtf8()+"-Hand#TXID:");
      QJsonValue playerTotal = cbStringKeys.value(handId.toUtf8()+"-Player total:");
      QJsonValue playerX = cbStringKeys.value(handId.toUtf8()+"-Player x:");
      QJsonValue playerY = cbStringKeys.value(handId.toUtf8()+"-Player y:");
      QJsonValue playerZ = cbStringKeys.value(handId.toUtf8()+"-Player z:");

      QJsonValue bankerTotal = cbStringKeys.value(handId.toUtf8()+"-Banker total:");
      QJsonValue bankerX = cbStringKeys.value(handId.toUtf8()+"-Banker x:");
      QJsonValue bankerY = cbStringKeys.value(handId.toUtf8()+"-Banker y:");
      QJsonValue bankerZ = cbStringKeys.value(handId.toUtf8()+"-Banker z:");

      ui->playerTotalSpinBox->setValue(playerTotal.toDouble());
      ui->playerXCardLabel->setPixmap(displayPlayerCards(playerX.toInt()));
      ui->playerYCardLabel->setPixmap(displayPlayerCards(playerY.toInt()));
      ui->playerZCardLabel->setPixmap(displayDrawPlayerCard(playerZ.toInt()));

      ui->bankerTotalSpinBox->setValue(bankerTotal.toDouble());
      ui->bankerXCardLabel->setPixmap(displayBankerCards(bankerX.toInt()));
      ui->bankerYCardLabel->setPixmap(displayBankerCards(bankerY.toInt()));
      ui->bankerZCardLabel->setPixmap(displayDrawBankerCard(bankerZ.toInt()));

      if(rpc::txidCheck == handTXID.toString())
      {
         ui->textBrowser->setText("Displaying hand TXID: "+handTXID.toString());
         rpc::foundHand = true;

         if(playerTotal.toInt() > bankerTotal.toInt())
         {
              ui->textBrowser->append("\nPlayer Wins");
              ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: rgb(79, 186, 196, 210); background-color: rgb(79, 186, 196, 21); };");
         }

         if(bankerTotal.toInt() > playerTotal.toInt())
         {
              ui->textBrowser->append("\nBanker Wins");
              ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: rgb(79, 186, 196, 210); background-color: rgb(79, 186, 196, 21); };");
         }

         if(bankerTotal.toInt() == playerTotal.toInt())
         {
              ui->textBrowser->append("\nTie");
              ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: rgb(56, 47, 165, 210); background-color: rgb(28, 31, 43, 0); };");
              ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: rgb(56, 47, 165, 210); background-color: rgb(28, 31, 43, 0); };");
         }

      }else{
          rpc::foundHand = false;
          std::cout << rpc::thisHand << std::endl;

      }

    }
    return 0;

}

int MainWindow::searchHandData(void)   /// Search hands stored on SC
{
    CURL *curlSearchHandData;
    CURLcode res;
    string readBuffer;

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\"da78f97e1aec885b8a3f75b1af2892dcd0a13342b645320e46cf0edf8c17478b\" , \"ringsize\":2 , \"code\":false , \"variables\":true}}";
    char error[CURL_ERROR_SIZE];
    QString daemonAddress =  ui->daemonRPCinput->text()+"/json_rpc";
    string dStr = daemonAddress.toStdString();
    const char *dCh = dStr.c_str ();

    loginInfo();
    const char *loginCh = rpc::rpcLogin.c_str ();


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
      curl_easy_setopt(curlSearchHandData, CURLOPT_POSTFIELDS, postthis);
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

      if(handTXID.isUndefined())
      {
          ui->textBrowser->setText("Error Hand Number Does Not Exist");
          blankCards();

      }else
      {
          ui->textBrowser->setText("Displaying hand TXID: "+handTXID.toString());
          if(playerTotal.toInt() > bankerTotal.toInt())
          {
               ui->textBrowser->append("\nPlayer Wins");
               ui->playerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: rgb(79, 186, 196, 210); background-color: rgb(79, 186, 196, 21); };");
          }

          if(bankerTotal.toInt() > playerTotal.toInt())
          {
               ui->textBrowser->append("\nBanker Wins");
               ui->bankerTotalSpinBox->setStyleSheet("QDoubleSpinBox{ border-color: rgb(79, 186, 196, 210); background-color: rgb(79, 186, 196, 21); };");
          }

          if(bankerTotal.toInt() == playerTotal.toInt())
          {
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
