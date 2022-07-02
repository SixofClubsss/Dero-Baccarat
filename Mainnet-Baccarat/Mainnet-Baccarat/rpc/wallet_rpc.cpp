#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "dialog.h"
#include "rpc.h"

using std::string;
string rpc::rpcLogin;
QString readout::deroAmount;
QString readout::chipAmount;
QString readout::tieAmount;
QString readout::bankerAmount;
QString readout::playerAmount;
QString readout::deroConverted;
QString readout::chipsConverted;
QString rpc::firstSigner;
QString rpc::txidCheck;
int rpc::thisHand;
bool rpc::connected;


void MainWindow::loginInfo()   /// Used to store wallet login info for all wallet functions
{
    QString userInfo = ui->userInput->text()+":";
    QString passInfo = ui->passwordInput->text();
    string userStr = userInfo.toStdString();
    string passStr = passInfo.toStdString();
    rpc::rpcLogin = userStr+passStr;
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


int MainWindow::sitDown()      /// When player connects wallet
{
    CURL *curlSitDown;
    CURLcode res;
    string sitDownReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\"eb0bfd7205a8753282ebf62a103451cdb30f161db301db742b50dc1b9f2a5c88\", \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"SitDown\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    QString playerAddress =  ui->walletRPCinput->text()+"/json_rpc";
    string pStr = playerAddress.toStdString();
    const char *gcCh = pStr.c_str ();

    loginInfo();
    const char *loginCh = rpc::rpcLogin.c_str ();

    curlSitDown = curl_easy_init();

    if(curlSitDown) {
      struct curl_slist *headers = NULL;

      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlSitDown, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlSitDown, CURLOPT_URL, gcCh);
      curl_easy_setopt(curlSitDown, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlSitDown, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlSitDown, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlSitDown, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlSitDown, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlSitDown, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlSitDown, CURLOPT_WRITEDATA, &sitDownReadBuffer);

      res = curl_easy_perform(curlSitDown);
      curl_easy_cleanup(curlSitDown);

    }
    return 0;
}


int MainWindow::leaveTable(void)      /// When player leaves
{
    CURL *curlLeave;
    CURLcode res;
    string leaveReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\"eb0bfd7205a8753282ebf62a103451cdb30f161db301db742b50dc1b9f2a5c88\", \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"Leave\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    QString playerAddress = ui->walletRPCinput->text()+"/json_rpc";
    string pStr = rpc::firstSigner.toStdString();
    const char *gcCh = pStr.c_str ();

    loginInfo();
    const char *loginCh = rpc::rpcLogin.c_str ();

    curlLeave = curl_easy_init();

    if(curlLeave) {
      struct curl_slist *headers = NULL;

      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlLeave, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlLeave, CURLOPT_URL, gcCh);
      curl_easy_setopt(curlLeave, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlLeave, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlLeave, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlLeave, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlLeave, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlLeave, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlLeave, CURLOPT_WRITEDATA, &leaveReadBuffer);

      res = curl_easy_perform(curlLeave);
      curl_easy_cleanup(curlLeave);

    }
    return 0;

}


int MainWindow::checkWallet()  /// Echo blockchain to confirm wallet is connected
{
    CURL *curlWalletCheck;      /// Set up cUrl
    CURLcode res;
    string readBuffer;

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\":\"1\",\"method\":\"Echo\", \"params\":[\"Hello\", \"World\", \"!\"]}";
    char error[CURL_ERROR_SIZE];
    QString walletAddress =  ui->walletRPCinput->text()+"/json_rpc";

    if(rpc::connected == false){
    rpc::firstSigner = walletAddress;
    }

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

      if(okCheck == "WALLET Hello World !"){
          if(rpc::connected == false){
              sitDown();
          }

          ui->walletConnectedBox->setChecked(true);      /// Wallet connected
          ui->textBrowser->setText("Wallet Connected");
          std::cout << "Wallet Connected" << std::endl;
          rpc::connected = true;
          ui->playerButton->setEnabled(true);
          ui->bankerButton->setEnabled(true);
          ui->tieButton->setEnabled(true);
          ui->getChipButton->setEnabled(true);
          ui->tradeChipButton->setEnabled(true);
          ui->playerBetAmount->setEnabled(true);
          ui->bankerBetAmount->setEnabled(true);
          ui->tieBetAmount->setEnabled(true);
          ui->getChipsAmount->setEnabled(true);
          ui->tradeChipsAmount->setEnabled(true);
          ui->minMaxLabel->setEnabled(true);

      }else {

          ui->walletConnectedBox->setChecked(false);
          ui->textBrowser->setText("Wallet Not Connected");
          std::cout << "Wallet Not Connected" << std::endl;      /// Wallet NOT connected

          if(rpc::connected == true){
              leaveTable();
              rpc::connected = false;
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

    QString dAmount = QString::number(ui->getChipsAmount->value()*100000);
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\"eb0bfd7205a8753282ebf62a103451cdb30f161db301db742b50dc1b9f2a5c88\", \"sc_dero_deposit\":"+dAmount+", \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"IssueChips\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

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
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\":[{\"scid\":\"dbfa9257e8cdaeacd35797402fd44e180c4c31c085989294c542c990706973d7\", \"burn\":"+cAmount+"}] ,\"scid\":\"eb0bfd7205a8753282ebf62a103451cdb30f161db301db742b50dc1b9f2a5c88\", \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"ConvertChips\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

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
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\": [{\"scid\":\"dbfa9257e8cdaeacd35797402fd44e180c4c31c085989294c542c990706973d7\", \"burn\":"+cAmount+"}],\"scid\":\"eb0bfd7205a8753282ebf62a103451cdb30f161db301db742b50dc1b9f2a5c88\",\"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"PlayBaccarat\"},{\"name\":\"betOn\",\"datatype\":\"S\",\"value\":\"player\" }]}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

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
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\": [{\"scid\":\"dbfa9257e8cdaeacd35797402fd44e180c4c31c085989294c542c990706973d7\", \"burn\":"+cAmount+"}],\"scid\":\"eb0bfd7205a8753282ebf62a103451cdb30f161db301db742b50dc1b9f2a5c88\",\"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"PlayBaccarat\"},{\"name\":\"betOn\",\"datatype\":\"S\",\"value\":\"banker\" }]}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

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
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\": [{\"scid\":\"dbfa9257e8cdaeacd35797402fd44e180c4c31c085989294c542c990706973d7\", \"burn\":"+cAmount+"}],\"scid\":\"eb0bfd7205a8753282ebf62a103451cdb30f161db301db742b50dc1b9f2a5c88\",\"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"PlayBaccarat\"},{\"name\":\"betOn\",\"datatype\":\"S\",\"value\":\"tie\" }]}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

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
