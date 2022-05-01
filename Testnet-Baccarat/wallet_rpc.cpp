#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "rpc.h"

using std::string;
string rpc::rpcLogin;

void MainWindow::loginInfo()   /// Used to store wallet login info for all wallet functions
{
    QString userInfo = ui->userInput->text()+":";
    QString passInfo = ui->passwordInput->text();
    string userStr = userInfo.toStdString();
    string passStr = passInfo.toStdString();
    rpc::rpcLogin = userStr+passStr;
}


int MainWindow::checkWallet(void)  /// Echo blockchain to confirm wallet is connected
{
    CURL *curlWalletCheck;      /// Set up cUrl
    CURLcode res;
    string readBuffer;

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\":\"1\",\"method\":\"Echo\",\"params\":[\"Hello\", \"World\", \"!\"]}";
    char error[CURL_ERROR_SIZE];
    QString walletAddress =  ui->walletRPCinput->text()+"/json_rpc";
    string pStr = walletAddress.toStdString();
    const char *pCh = pStr.c_str ();

    loginInfo();            /// Get login info
    const char *loginCh = rpc::rpcLogin.c_str ();

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
      curl_easy_setopt(curlWalletCheck, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlWalletCheck, CURLOPT_ERRORBUFFER, error);
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

      std::cout << readBuffer << std::endl;

      if(okCheck == "WALLET Hello World !")
      {
         ui->walletConnectedBox->setChecked(true);      /// Wallet connected

          ui->textBrowser->setText("Wallet Connected");
          std::cout << "Wallet Connected" << std::endl;
      }else {

          ui->walletConnectedBox->setChecked(false);
          ui->textBrowser->setText("Wallet Not Connected");
         std::cout << "Wallet Not Connected" << std::endl;      /// Wallet NOT connected
      }


    }
    return 0;
}


int MainWindow::getChips(void)      /// Trade Testnet Dero for Chips token (Only Chips are accepted for bets)
{
    CURL *curlGetChips;
    CURLcode res;
    string getChipsReadBuffer;

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\"8817f03755a562cc1f34c6e90389ef9cc416a32d6084c0ebb4b245bc76da5c9d\", \"sc_dero_deposit\":50000 , \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"IssueChips\"}] }}";
    char error[CURL_ERROR_SIZE];
    QString playerAddress =  ui->walletRPCinput->text()+"/json_rpc";
    string pStr = playerAddress.toStdString();
    const char *gcCh = pStr.c_str ();

    loginInfo();
    const char *loginCh = rpc::rpcLogin.c_str ();

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
      curl_easy_setopt(curlGetChips, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlGetChips, CURLOPT_ERRORBUFFER, error);
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

      std::cout << getChipsReadBuffer << std::endl;

      if(getChipsTxid.isString())
      {
          ui->textBrowser->setText("Get Chips TXID: "+getChipsTxid.toString());  /// Displays TXID and adds TXID to session log
          ui->logTextBrowser->append("TXID: "+getChipsTxid.toString()+"\n");

      }else
       {
          ui->textBrowser->setText("Error No Get Chips TXID");      /// No TXID was recieved
       }

    }
    return 0;
}


int MainWindow::tradeChips(void)        /// Trade Chips for Testnet Dero
{
    CURL *curlTradeChips;
    CURLcode res;
    string tradeChipsReadBuffer;

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\":[{\"scid\":\"a30c6602a791fae5464b974ca268e3720c2bae870d20804a8694b0f0917b8bce\", \"burn\":100000}],\"scid\":\"8817f03755a562cc1f34c6e90389ef9cc416a32d6084c0ebb4b245bc76da5c9d\", \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"ConvertChips\"}] }}";
    char error[CURL_ERROR_SIZE];
    QString playerAddress =  ui->walletRPCinput->text()+"/json_rpc";
    string pStr = playerAddress.toStdString();
    const char *tcCh = pStr.c_str ();

    loginInfo();
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
      curl_easy_setopt(curlTradeChips, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlTradeChips, CURLOPT_ERRORBUFFER, error);
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

      std::cout << tradeChipsReadBuffer << std::endl;

      if(tradeChipsTxid.isString())
      {
          ui->textBrowser->setText("Trade Chips TXID: "+tradeChipsTxid.toString());
          ui->logTextBrowser->append("TXID: "+tradeChipsTxid.toString()+"\n");

      }else
       {
          ui->textBrowser->setText("Error No Trade Chips TXID");
       }

    }
    return 0;
}


int MainWindow::playerBet(void)     /// Bet 0.1 Chip on player
{
    CURL *curlPlayer;
    CURLcode res;
    string pReadBuffer;

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\": [{\"scid\":\"a30c6602a791fae5464b974ca268e3720c2bae870d20804a8694b0f0917b8bce\", \"burn\":10000 }],\"scid\":\"8817f03755a562cc1f34c6e90389ef9cc416a32d6084c0ebb4b245bc76da5c9d\",\"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"PlayBaccarat\"},{\"name\":\"betOn\",\"datatype\":\"S\",\"value\":\"player\" }]}}";
    char error[CURL_ERROR_SIZE];
    QString playerAddress =  ui->walletRPCinput->text()+"/json_rpc";
    string pStr = playerAddress.toStdString();
    const char *pCh = pStr.c_str ();

    loginInfo();
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
      curl_easy_setopt(curlPlayer, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlPlayer, CURLOPT_ERRORBUFFER, error);
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

      std::cout << pReadBuffer << std::endl;

        if(txid.isString())
        {
            ui->textBrowser->setText("Your Hand TXID: "+txid.toString());
            ui->textBrowser->append("\nHand results will display in 30 seconds");
            ui->logTextBrowser->append("TXID: "+txid.toString()+"\n");

        }else
         {
            ui->textBrowser->setText("Error No Hand TXID");
         }
    }
    return 0;
}


int MainWindow::bankerBet(void)     /// Bet 0.1 Chip on banker
{
    CURL *curlBanker;
    CURLcode res;
    string bReadBuffer;

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\": [{\"scid\":\"a30c6602a791fae5464b974ca268e3720c2bae870d20804a8694b0f0917b8bce\", \"burn\":10000 }],\"scid\":\"8817f03755a562cc1f34c6e90389ef9cc416a32d6084c0ebb4b245bc76da5c9d\",\"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"PlayBaccarat\"},{\"name\":\"betOn\",\"datatype\":\"S\",\"value\":\"banker\" }]}}";
    char error[CURL_ERROR_SIZE];
    QString playerAddress =  ui->walletRPCinput->text()+"/json_rpc";
    string pStr = playerAddress.toStdString();
    const char *pCh = pStr.c_str ();

    loginInfo();
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
      curl_easy_setopt(curlBanker, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlBanker, CURLOPT_ERRORBUFFER, error);
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

      std::cout << bReadBuffer << std::endl;

      if(txid.isString())
      {
          ui->textBrowser->setText("Your Hand TXID: "+txid.toString());
          ui->textBrowser->append("\nHand results will display in 30 seconds");
          ui->logTextBrowser->append("TXID: "+txid.toString()+"\n");

      }else
       {
          ui->textBrowser->setText("Error No Hand TXID");
       }
    }
    return 0;
}


int MainWindow::tieBet(void)            /// Bet 0.1 Chip on tie
{
    CURL *curlTie;
    CURLcode res;
    string tReadBuffer;

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\": [{\"scid\":\"a30c6602a791fae5464b974ca268e3720c2bae870d20804a8694b0f0917b8bce\", \"burn\":10000 }],\"scid\":\"8817f03755a562cc1f34c6e90389ef9cc416a32d6084c0ebb4b245bc76da5c9d\",\"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"PlayBaccarat\"},{\"name\":\"betOn\",\"datatype\":\"S\",\"value\":\"tie\" }]}}";
    char error[CURL_ERROR_SIZE];
    QString playerAddress =  ui->walletRPCinput->text()+"/json_rpc";
    string pStr = playerAddress.toStdString();
    const char *tCh = pStr.c_str ();

    loginInfo();
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
      curl_easy_setopt(curlTie, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlTie, CURLOPT_ERRORBUFFER, error);
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

      std::cout << tReadBuffer << std::endl;

        if(txid.isString())
        {
            ui->textBrowser->setText("Your Hand TXID: "+txid.toString());
            ui->textBrowser->append("\nHand results will display in 30 seconds");
            ui->logTextBrowser->append("TXID: "+txid.toString()+"\n");

        }else
         {
            ui->textBrowser->setText("Error No Hand TXID");
         }
    }
    return 0;
}
