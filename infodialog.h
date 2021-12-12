#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include "cocktail.h"
#include <QAbstractButton>
#include <QHBoxLayout>


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
    QMap<QAbstractButton *, Cocktail> buttonCocktailMap; // Stores dynamically created buttons.
    QButtonGroup cocktailButtons; // Button group to use all of the dynamically created buttons.
    QVector<QHBoxLayout*> statEntries; // Used to manage memory in the stat layout. Stores layouts with labels in them.

    void setInfoPage();
    void setContentsPage();
    void populateInfo(Cocktail &drink);
    void cocktailClicked(QAbstractButton *);
    void clearStatsLayout();
    void populateStatsLayout(Cocktail &drink);

};

#endif // INFODIALOG_H
