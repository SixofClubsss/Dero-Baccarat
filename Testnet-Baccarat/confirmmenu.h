#ifndef CONFIRMMENU_H
#define CONFIRMMENU_H

#include "QDialog"
#include "mainwindow.h"
#include "rpc.h"


namespace Ui {
class confirmmenu;
}

class confirmmenu : public QDialog
{
    Q_OBJECT

public:
    explicit confirmmenu(QWidget *parent = nullptr);
    ~confirmmenu();

     void playerConfirmText();
     void bankerConfirmText();
     void tieConfirmText();
     void getConfirmText();
     void tradeConfirmText();
     static int whichBet;
     static bool betConfirmed;


private slots:
     void on_buttonBox_accepted();

private:
     Ui::confirmmenu *ui;
};

#endif // CONFIRMMENU_H
