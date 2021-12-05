#include "infodialog.h"
#include "ui_infodialog.h"
#include "cocktail.h"

InfoDialog::InfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog)
{
    ui->setupUi(this);

    // Start on the first page.
    setContentsPage();

    // Move background image to the back of info page.
    ui->backgroundInfo->lower();
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

void InfoDialog::populateInfo(Cocktail::name cocktailName)
{
    Cocktail drink = localList[cocktailName];
    ui->nameEntry->setText(drink.getNameString());
}

void InfoDialog::displayCocktails(QMap<Cocktail::name, Cocktail> list)
{
    localList = list;
}

void InfoDialog::on_oldFashionedButton_clicked()
{
    populateInfo(Cocktail::oldFashioned);
    setInfoPage();
}

void InfoDialog::on_margaritaButton_clicked()
{
    populateInfo(Cocktail::margarita);
    setInfoPage();
}

void InfoDialog::on_moscowMuleButton_clicked()
{
    populateInfo(Cocktail::moscowMule);
    setInfoPage();
}

void InfoDialog::on_kentuckyMuleButton_clicked()
{
    populateInfo(Cocktail::kentuckyMule);
    setInfoPage();
}

void InfoDialog::on_martiniButton_clicked()
{
    populateInfo(Cocktail::martini);
    setInfoPage();
}

void InfoDialog::on_mojitoButton_clicked()
{
    populateInfo(Cocktail::mojito);
    setInfoPage();
}

void InfoDialog::on_whiskeySourButton_clicked()
{
    populateInfo(Cocktail::whiskeySour);
    setInfoPage();
}

void InfoDialog::on_manhattanButton_clicked()
{
    populateInfo(Cocktail::manhattan);
    setInfoPage();
}

void InfoDialog::on_gimletButton_clicked()
{
    populateInfo(Cocktail::gimlet);
    setInfoPage();
}

void InfoDialog::on_cosmopolitanButton_clicked()
{
    populateInfo(Cocktail::cosmopolitan);
    setInfoPage();
}

void InfoDialog::on_negroniButton_clicked()
{
    populateInfo(Cocktail::negroni);
    setInfoPage();
}

void InfoDialog::on_mimosaButton_clicked()
{
    populateInfo(Cocktail::mimosa);
    setInfoPage();
}

void InfoDialog::on_palomaButton_clicked()
{
    populateInfo(Cocktail::paloma);
    setInfoPage();
}

void InfoDialog::on_sidecarButton_clicked()
{
    populateInfo(Cocktail::sidecar);
    setInfoPage();
}

void InfoDialog::on_mintJulepButton_clicked()
{
    populateInfo(Cocktail::mintJulep);
    setInfoPage();
}

void InfoDialog::on_daiquiriButton_clicked()
{
    populateInfo(Cocktail::daiquiri);
    setInfoPage();
}

void InfoDialog::on_screwDriverButton_clicked()
{
    populateInfo(Cocktail::screwDriver);
    setInfoPage();
}

void InfoDialog::on_whiteRussianButton_clicked()
{
    populateInfo(Cocktail::whiteRussian);
    setInfoPage();
}

void InfoDialog::on_homeButton_clicked()
{
    setContentsPage();
}

