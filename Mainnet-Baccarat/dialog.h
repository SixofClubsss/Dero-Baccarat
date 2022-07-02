#ifndef DIALOG_H
#define DIALOG_H

#include "QDialog"


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void setFonts();
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
    Ui::Dialog *ui;
};

class readout
{

public:
    static QString deroAmount;
    static QString chipAmount;
    static QString tieAmount;
    static QString bankerAmount;
    static QString playerAmount;
    static QString deroConverted;
    static QString chipsConverted;
};

#endif // DIALOG_H
