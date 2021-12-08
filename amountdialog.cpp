#include "amountdialog.h"
#include "ui_amountdialog.h"

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
