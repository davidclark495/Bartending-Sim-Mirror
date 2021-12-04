#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include "cocktail.h"

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(QWidget *parent = nullptr);
    ~InfoDialog();

signals:
    void requestCocktails();

private slots:
    void recieveCocktails(QVector<Cocktail> list);


private:
    Ui::InfoDialog *ui;
};

#endif // INFODIALOG_H
