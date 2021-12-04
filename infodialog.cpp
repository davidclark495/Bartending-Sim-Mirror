#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog)
{
    ui->setupUi(this);

    // Start on the first page.
    setContentsPage();
}

InfoDialog::~InfoDialog()
{
    delete ui;
}

void InfoDialog::setInfoPage()
{
    ui->pages->setCurrentIndex(1);
}

void InfoDialog::setContentsPage()
{
    ui->pages->setCurrentIndex(0);
}

void InfoDialog::recieveCocktails(QVector<Cocktail> list)
{
    list.clear();
}

void InfoDialog::on_oldFashionedButton_clicked()
{
    setInfoPage();
}



void InfoDialog::on_pushButton_clicked()
{
    setContentsPage();
}


void InfoDialog::on_margaritaButton_clicked()
{
    setInfoPage();
}


void InfoDialog::on_moscowMuleButton_clicked()
{
    setInfoPage();
}


void InfoDialog::on_kentuckyMuleButton_clicked()
{
    setInfoPage();
}


void InfoDialog::on_martiniButton_clicked()
{
    setInfoPage();
}


void InfoDialog::on_mojitoButton_clicked()
{
    setInfoPage();
}


void InfoDialog::on_whiskeySourButton_clicked()
{
    setInfoPage();
}


void InfoDialog::on_manhattanButton_clicked()
{
    setInfoPage();
}


void InfoDialog::on_gimletButton_clicked()
{
    setInfoPage();
}


void InfoDialog::on_cosmopolitanButton_clicked()
{
    setInfoPage();
}


void InfoDialog::on_negroniButton_clicked()
{
    setInfoPage();
}


void InfoDialog::on_mimosaButton_clicked()
{
    setInfoPage();
}


void InfoDialog::on_palomaButton_clicked()
{
    setInfoPage();
}


void InfoDialog::on_sidecarButton_clicked()
{
    setInfoPage();
}


void InfoDialog::on_mintJulepButton_clicked()
{
    setInfoPage();
}


void InfoDialog::on_daiquiriButton_clicked()
{
    setInfoPage();
}


void InfoDialog::on_screwDriverButton_clicked()
{
    setInfoPage();
}


void InfoDialog::on_whiteRussianButton_clicked()
{
    setInfoPage();
}

