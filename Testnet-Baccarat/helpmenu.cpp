#include "helpmenu.h"
#include "ui_helpmenu.h"

helpmenu::helpmenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helpmenu)
{
    ui->setupUi(this);
}

helpmenu::~helpmenu()
{
    delete ui;
}
