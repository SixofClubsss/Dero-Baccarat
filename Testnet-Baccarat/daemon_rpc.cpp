#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "rpc.h"


using std::string;


void MainWindow::delay()            /// Delay in to help with data read out
{
    QTime dieTime= QTime::currentTime().addSecs(30);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


int MainWindow::fetchScData(void)       /// Get SC variables
{
    CURL *curlFetch;        /// Set up cUrl
    CURLcode res;
    string fetchReadBuffer;

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\"8817f03755a562cc1f34c6e90389ef9cc416a32d6084c0ebb4b245bc76da5c9d\" , \"ringsize\":2 , \"code\":false , \"variables\":true}}";
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

      ui->dsbTotalHandsPlayed->setValue(totalHands.toDouble()); /// Updates total hands played display

    }
    return 0;
}


int MainWindow::checkDaemon(void)       /// Check connection to daemon
{
    CURL *curlDaemonCheck;
    CURLcode res;
    string readBuffer;

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\"8817f03755a562cc1f34c6e90389ef9cc416a32d6084c0ebb4b245bc76da5c9d\" , \"ringsize\":2 , \"code\":false , \"variables\":false}}";
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

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\"8817f03755a562cc1f34c6e90389ef9cc416a32d6084c0ebb4b245bc76da5c9d\" , \"ringsize\":2 , \"code\":false , \"variables\":true}}";
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

      std::cout << readBuffer << std::endl;

      QByteArray br = readBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonObject cbStringKeys = cbResults["stringkeys"].toObject();

      int checkTotalHands = ui->dsbTotalHandsPlayed->value();
      QString handId = QString::number(checkTotalHands);

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

      ui->textBrowser->setText("Displaying hand TXID: "+handTXID.toString());

    }
    return 0;

}


void MainWindow::blankCards()
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


QPixmap MainWindow::displayPlayerCards(int card) /// To Convert Player int card vlaue to card symbol
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

QPixmap MainWindow::displayBankerCards(int card) /// To Convert Player int card vlaue to card symbol
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

QPixmap MainWindow::displayDrawPlayerCard(int card) /// To Convert Player int card vlaue to card symbol
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


QPixmap MainWindow::displayDrawBankerCard(int card) /// To Convert Banker int card vlaue to card symbol
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
