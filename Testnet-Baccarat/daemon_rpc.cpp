#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "rpc.h"


using std::string;


void MainWindow::delay()            /// Delay in to help with data read out
{
    QTime dieTime= QTime::currentTime().addSecs(3);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


int MainWindow::fetchScData(void)       /// Get SC variables
{
    CURL *curlFetch;        /// Set up cUrl
    CURLcode res;
    string fetchReadBuffer;                                                                                                                                                                                                                                    ///// \"keysstring\":[\"TotalHandsPlayed:\" , \"1-Banker total:\"

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
    string readBuffer;                                                                                                                                                                                                                                      ///// \"keysstring\":[\"TotalHandsPlayed:\" , \"1-Banker total:\"

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
