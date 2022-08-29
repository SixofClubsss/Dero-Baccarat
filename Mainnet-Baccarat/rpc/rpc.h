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
using std::string;

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
    static QString walletAddress;
    static QString contractAddress;
    static QString tokenAddress;
    static QString daemonAddress;
    static QString txidCheck;
    static QString foundHandTXID;
    static bool walletConnected;
    static bool daemonConnected;
    static bool foundHand;
    static double deroBalance;
    static double dReamBalance;
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

    int getDeroBalance();
    int getdReamBalance();
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
        if(rpc::walletConnected == true){
        rpcData.getDeroBalance();
        rpcData.getdReamBalance();
        }
        if(rpc::daemonConnected == true){
            rpcData.getHeight();
            rpcData.fetchScData();
        }

    }

};

#endif // RPC_H
