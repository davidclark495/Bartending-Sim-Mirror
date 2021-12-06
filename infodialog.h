#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include "cocktail.h"
#include <QAbstractButton>


namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(QWidget *parent = nullptr);
    ~InfoDialog();

public slots:
    void displayCocktails(QVector<Cocktail> list);

private slots:
    void on_homeButton_clicked();

private:
    Ui::InfoDialog *ui;
    QMap<QAbstractButton *, Cocktail> localList;
    QButtonGroup cocktailButtons;

    void setInfoPage();
    void setContentsPage();
    void populateInfo(Cocktail drink);
    void cocktailClicked(QAbstractButton *);
};

#endif // INFODIALOG_H
