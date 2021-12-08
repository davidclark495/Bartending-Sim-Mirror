#ifndef AMOUNTDIALOG_H
#define AMOUNTDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include "cocktail.h"

namespace Ui {
class AmountDialog;
}

class AmountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AmountDialog(QWidget *parent = nullptr);
    ~AmountDialog();

public slots:
    void populateInformation(QButtonGroup alcoholList, QButtonGroup mixerList, QButtonGroup garnishList, QButtonGroup glassList);

signals:


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AmountDialog *ui;

    void clearInfo();
};

#endif // AMOUNTDIALOG_H
