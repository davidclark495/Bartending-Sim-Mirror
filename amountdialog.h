#ifndef AMOUNTDIALOG_H
#define AMOUNTDIALOG_H

#include <QDialog>
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
    void displayCocktails(QVector<Cocktail> list);

signals:


private:
    Ui::AmountDialog *ui;
};

#endif // AMOUNTDIALOG_H
