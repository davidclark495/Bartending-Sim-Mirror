#include "amountdialog.h"
#include "ui_amountdialog.h"
#include <QButtonGroup>

AmountDialog::AmountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AmountDialog)
{
    ui->setupUi(this);
}

AmountDialog::~AmountDialog()
{
    delete ui;
}

void AmountDialog::populateInformation(QButtonGroup &alcoholList, QButtonGroup &mixerList, QButtonGroup &garnishList, QButtonGroup &glassList)
{
    clearInfo();
}

void AmountDialog::clearInfo()
{

}

void AmountDialog::on_buttonBox_accepted()
{

}


void AmountDialog::on_buttonBox_rejected()
{

}

