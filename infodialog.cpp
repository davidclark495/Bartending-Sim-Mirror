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

    connect(&cocktailButtons, &QButtonGroup::buttonClicked, this, &InfoDialog::cocktailClicked);
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

void InfoDialog::populateInfo(Cocktail drink)
{
    ui->nameEntry->setText(drink.getName());
    ui->difficultyEntry->setText(drink.getDifficulty());
    ui->descriptionEntry->setText(drink.getDescription());
    ui->iceEntry->setText(drink.getIce());
    ui->glassEntry->setText(drink.getGlass());
    ui->ingredientsEntry->setText(drink.getIngredients());
    ui->garnishEntry->setText(drink.getGarnish());
    ui->instructionsEntry->setText(drink.getInstructions());
}

void InfoDialog::displayCocktails(QVector<Cocktail> list)
{
    // Prevent buttons from being re-added to the screen.
    if(localList.size() != 0 )
        return;

    int numButtonsLeft = list.count() / 2;

    // Left page of contents.
    for(int i = 0; i < numButtonsLeft; ++i)
    {
        QPushButton* button = new QPushButton(list[i].getName());
        localList[button] = list[i];
        ui->contentsLeftPage->addWidget(button);
        cocktailButtons.addButton(button);
    }

    // Right page of contents.
    for(int i = numButtonsLeft; i < list.count(); ++i)
    {
        QPushButton* button = new QPushButton(list[i].getName());
        localList[button] = list[i];
        ui->contentsRightPage->addWidget(button);
        cocktailButtons.addButton(button);
    }
}

void InfoDialog::cocktailClicked(QAbstractButton* button)
{
    populateInfo(localList[button]);
    setInfoPage();
}

void InfoDialog::on_homeButton_clicked()
{
    setContentsPage();
}

