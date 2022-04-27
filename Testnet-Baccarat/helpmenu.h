#ifndef HELPMENU_H
#define HELPMENU_H

#include "QDialog"

namespace Ui {
class helpmenu;
}

class helpmenu : public QDialog
{
    Q_OBJECT

public:
    explicit helpmenu(QWidget *parent = nullptr);
    ~helpmenu();

private:
    Ui::helpmenu *ui;
};

#endif // HELPMENU_H
