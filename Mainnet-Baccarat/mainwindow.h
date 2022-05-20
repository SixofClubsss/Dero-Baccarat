#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QMainWindow"
#include "iostream"
#include "dialog.h"
#include "dialog.h"

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
    int sitDown(void);
    int leaveTable(void);
    int fetchScData(void);
    int fetchHandData(void);
    int searchHandData(void);
    int checkDaemon(void);
    int checkWallet(void);
    int getChips(void);
    int tradeChips(void);
    int playerBet(void);
    int bankerBet(void);
    int tieBet(void);
    void findMyHand();
    void blankCards();
    void readoutConfirm();
    QPixmap displayPlayerCards(int);
    QPixmap displayBankerCards(int);
    QPixmap displayDrawPlayerCard(int);
    QPixmap displayDrawBankerCard(int);

private slots:

    void refresh();

    void on_playerButton_clicked();

    void on_daemonRPCbutton_clicked(bool checked);

    void on_walletRPCbutton_clicked(bool checked);

    void on_bankerButton_clicked();

    void on_getChipButton_clicked();

    void on_tradeChipButton_clicked();

    void on_tieButton_clicked();

    void on_helpButton_clicked();

    void on_reloadButton_clicked();


    void on_searchButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

