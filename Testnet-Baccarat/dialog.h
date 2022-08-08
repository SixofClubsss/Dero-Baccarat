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
