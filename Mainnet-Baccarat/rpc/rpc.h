#ifndef RPC_H
#define RPC_H

#include "string"
#include "curl/curl.h"
#include "QTime"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonValue"
#include "QJsonArray"
#include "QString"
#include "QTime"
#include "QThread"


static size_t
WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

class rpc
{

public:
    static std::string rpcLogin;
    static QString contractAddress;
    static QString tokenAddress;
    static QString daemonAddress;
    static QString txidCheck;
    static QString foundHandTXID;
    static bool connected;
    static bool foundHand;
    static double totalHands;
    static double foundPlayerTotal;
    static double foundBankerTotal;
    static int thisHand;
    static int playerWins;
    static int bankerWins;
    static int totalTies;
    static int foundPlayerX;
    static int foundPlayerY;
    static int foundPlayerZ;
    static int foundBankerX;
    static int foundBankerY;
    static int foundBankerZ;
    static int blockHeight;

    int getHeight();
    int fetchScData();
};


class Worker : public QObject
{
    Q_OBJECT

public:
    static QThread workThread;

private slots:
    void onTimeout()
    {
        rpc rpcData;
        rpcData.getHeight();
        rpcData.fetchScData();
    }

};

#endif // RPC_H
