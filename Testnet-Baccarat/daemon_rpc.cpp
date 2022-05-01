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
      ui->playerXCardLabel->setText(displayPlayerCards(playerX.toInt()));
      ui->playerYCardLabel->setText(displayPlayerCards(playerY.toInt()));
      ui->playerZCardLabel->setText(displayDrawPlayerCard(playerZ.toInt()));

      ui->bankerTotalSpinBox->setValue(bankerTotal.toDouble());
      ui->bankerXCardLabel->setText(displayBankerCards(bankerX.toInt()));
      ui->bankerYCardLabel->setText(displayBankerCards(bankerY.toInt()));
      ui->bankerZCardLabel->setText(displayDrawBankerCard(bankerZ.toInt()));

      ui->textBrowser->setText("Displaying hand TXID: "+handTXID.toString());

    }
    return 0;

}


void MainWindow::blankCards()
{
    ui->playerTotalSpinBox->setValue(0);
    ui->playerXCardLabel->setText("🂠");
    ui->playerYCardLabel->setText("🂠");
    ui->playerZCardLabel->setText("🂠");

    ui->bankerTotalSpinBox->setValue(0);
    ui->bankerXCardLabel->setText("🂠");
    ui->bankerYCardLabel->setText("🂠");
    ui->bankerZCardLabel->setText("🂠");
}


QString MainWindow::displayPlayerCards(int card) /// To Convert Player int card vlaue to card symbol
{
    QString pcardEquiv;
        switch(card){
        case 0: pcardEquiv = "🂼"; break;
        case 1: pcardEquiv = "🂱"; break;
        case 2: pcardEquiv = "🂲"; break;
        case 3: pcardEquiv ="🂳"; break;
        case 4: pcardEquiv ="🂴"; break;
        case 5: pcardEquiv ="🂵"; break;
        case 6: pcardEquiv ="🂶"; break;
        case 7: pcardEquiv ="🂷"; break;
        case 8: pcardEquiv ="🂸"; break;
        case 9: pcardEquiv ="🂹"; break;
        case 10: pcardEquiv ="🂼"; break;
        case 11: pcardEquiv ="🂼"; break;
        case 12: pcardEquiv = "🂼"; break;
        case 13: pcardEquiv = "🂼"; break;
        }

    return pcardEquiv;
}


QString MainWindow::displayBankerCards(int card) /// To Convert Banker int card vlaue to card symbol
{
    QString cardEquiv;
    switch(card){
    case 0: cardEquiv = "🃜"; break;
    case 1: cardEquiv = "🃑"; break;
    case 2: cardEquiv = "🃒"; break;
    case 3: cardEquiv = "🃓"; break;
    case 4: cardEquiv = "🃔"; break;
    case 5: cardEquiv = "🃕"; break;
    case 6: cardEquiv = "🃖"; break;
    case 7: cardEquiv = "🃗"; break;
    case 8: cardEquiv = "🃘"; break;
    case 9: cardEquiv = "🃙"; break;
    case 10: cardEquiv = "🃜"; break;
    case 11: cardEquiv = "🃜"; break;
    case 12: cardEquiv = "🃜"; break;
    case 13: cardEquiv = "🃜"; break;
    }
    return cardEquiv;
}

QString MainWindow::displayDrawPlayerCard(int card) /// To Convert Banker int card vlaue to card symbol
{
    QString pdrawCardEquiv;
    switch(card){
    case 0: pdrawCardEquiv = "🂠"; break;
    case 1: pdrawCardEquiv = "🂱"; break;
    case 2: pdrawCardEquiv = "🂲"; break;
    case 3: pdrawCardEquiv = "🂳"; break;
    case 4: pdrawCardEquiv = "🂴"; break;
    case 5: pdrawCardEquiv = "🂵"; break;
    case 6: pdrawCardEquiv = "🂶"; break;
    case 7: pdrawCardEquiv = "🂷"; break;
    case 8: pdrawCardEquiv = "🂸"; break;
    case 9: pdrawCardEquiv = "🂹"; break;
    case 10: pdrawCardEquiv = "🂼"; break;
    case 11: pdrawCardEquiv = "🂼"; break;
    case 12: pdrawCardEquiv = "🂼"; break;
    case 13: pdrawCardEquiv = "🂼"; break;
    }
    return pdrawCardEquiv;
}


QString MainWindow::displayDrawBankerCard(int card) /// To Convert Banker int card vlaue to card symbol
{
    QString drawCardEquiv;
    switch(card){
    case 0: drawCardEquiv = "🂠"; break;
    case 1: drawCardEquiv = "🃑"; break;
    case 2: drawCardEquiv = "🃒"; break;
    case 3: drawCardEquiv = "🃓"; break;
    case 4: drawCardEquiv = "🃔"; break;
    case 5: drawCardEquiv = "🃕"; break;
    case 6: drawCardEquiv = "🃖"; break;
    case 7: drawCardEquiv = "🃗"; break;
    case 8: drawCardEquiv = "🃘"; break;
    case 9: drawCardEquiv = "🃙"; break;
    case 10: drawCardEquiv = "🃜"; break;
    case 11: drawCardEquiv = "🃜"; break;
    case 12: drawCardEquiv = "🃜"; break;
    case 13: drawCardEquiv = "🃜"; break;
    }
    return drawCardEquiv;
}
