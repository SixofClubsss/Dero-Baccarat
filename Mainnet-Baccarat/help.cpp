#include "help.h"
#include "ui_help.h"
#include "mainwindow.h"

Help::Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    setFonts();
}

Help::~Help()
{
    delete ui;
}

void Help::setFonts()
{
    int fontId = QFontDatabase::addApplicationFont(":/fonts/Macondo-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont macondoRegular12(fontFamily);
    macondoRegular12.setPointSize(11);
    macondoRegular12.setBold(true);
    ui->dReamsLabel->setFont(macondoRegular12);

    int fontId2 = QFontDatabase::addApplicationFont(":/fonts/Ubuntu-R.ttf");
    QString fontFamily2 = QFontDatabase::applicationFontFamilies(fontId2).at(0);
    QFont ubuntuRegular(fontFamily2);
    ubuntuRegular.setPointSize(10);
    ui->buttonBox->setFont(ubuntuRegular);
}
