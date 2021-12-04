#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QButtonGroup>
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


    void on_oldFashionedButton_clicked();

    void on_pushButton_clicked();

    void on_margaritaButton_clicked();

    void on_moscowMuleButton_clicked();

    void on_kentuckyMuleButton_clicked();

    void on_martiniButton_clicked();

    void on_mojitoButton_clicked();

    void on_whiskeySourButton_clicked();

    void on_manhattanButton_clicked();

    void on_gimletButton_clicked();

    void on_cosmopolitanButton_clicked();

    void on_negroniButton_clicked();

    void on_mimosaButton_clicked();

    void on_palomaButton_clicked();

    void on_sidecarButton_clicked();

    void on_mintJulepButton_clicked();

    void on_daiquiriButton_clicked();

    void on_screwDriverButton_clicked();

    void on_whiteRussianButton_clicked();

private:
    Ui::InfoDialog *ui;
    void setInfoPage();
    void setContentsPage();
};

#endif // INFODIALOG_H
