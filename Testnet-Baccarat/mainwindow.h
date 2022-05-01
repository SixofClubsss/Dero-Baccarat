#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QMainWindow"
#include "iostream"
///#include "string"
///#include "curl/curl.h"
#include "confirmmenu.h"
#include "ui_confirmmenu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loginInfo();
    void delay();
    int fetchScData(void);
    int fetchHandData(void);
    int checkDaemon(void);
    int checkWallet(void);
    int getChips(void);
    int tradeChips(void);
    int playerBet(void);
    int bankerBet(void);
    int tieBet(void);
    void blankCards();
    QString displayPlayerCards(int);
    QString displayBankerCards(int);
    QString displayDrawPlayerCard(int);
    QString displayDrawBankerCard(int);



private slots:

    void on_playerButton_clicked();

    void on_daemonRPCbutton_clicked(bool checked);

    void on_walletRPCbutton_clicked(bool checked);

    void on_bankerButton_clicked();

    void on_getChipButton_clicked();

    void on_tradeChipButton_clicked();

    void on_tieButton_clicked();

    void on_helpButton_clicked();

    void on_reloadButton_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
