/**
 * A9 - Bartending Simulator
 *
 *  Author:  David McLean - u0145629
 *  Author:  Grayson Spencer - u1103228.
 *  Author:  David Clark - u1225394
 *  Author:  Zachary Atherton - u1023217
 *  Class:   C3505 Fall 2021
 *  Date:   12/16/2021
 *
 *  Style Checked by :
 **/
#include <QHBoxLayout>
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

void InfoDialog::cocktailClicked(QAbstractButton* button)
{
    populateInfo(buttonCocktailMap[button]);
    setInfoPage();
}

void InfoDialog::on_homeButton_clicked()
{
    setContentsPage();
}

void InfoDialog::setInfoPage()
{
    ui->pages->setCurrentIndex(1);
}

void InfoDialog::setContentsPage()
{
    ui->pages->setCurrentIndex(0);
}

void InfoDialog::populateInfo(Cocktail &drink)
{
    ui->nameEntry->setText(drink.getName());
    ui->difficultyEntry->setText(drink.getDifficulty());
    ui->descriptionEntry->setText(drink.getDescription());
    ui->iceEntry->setText(drink.getIce());
    ui->glassEntry->setText(drink.getGlass());
    ui->ingredientsEntry->setText(drink.getIngredientString());
    ui->garnishEntry->setText(drink.getGarnishString());
    ui->instructionsEntry->setText(drink.getInstructions());
    ui->demoCocktail->setStyleSheet("image: url(" + drink.getReferenceImage() + ")" );

    clearStatsLayout();
    populateStatsLayout(drink);
}

void InfoDialog::displayCocktails(QVector<Cocktail> list)
{
    setContentsPage();

    // If the map has already been populated we need to clear all the buttons from map and group.
    if(buttonCocktailMap.size() != 0 )
    {
        buttonCocktailMap.clear();
        foreach (QAbstractButton *button, cocktailButtons.buttons())
        {
            button->deleteLater();
        }
    }

    int numButtonsLeft = list.count() / 2;

    // Left page of contents.
    for(int i = 0; i < numButtonsLeft; ++i)
    {
        QPushButton* button = new QPushButton(list[i].getName());
        buttonCocktailMap[button] = list[i];
        ui->contentsLeftPage->addWidget(button);
        cocktailButtons.addButton(button);
    }

    // Right page of contents.
    for(int i = numButtonsLeft; i < list.count(); ++i)
    {
        QPushButton* button = new QPushButton(list[i].getName());
        buttonCocktailMap[button] = list[i];
        ui->contentsRightPage->addWidget(button);
        cocktailButtons.addButton(button);
    }
}

// Modified from QT documentation to hopefully avoid memory leaks.
void InfoDialog::clearStatsLayout()
{
    QLayoutItem *child;

    // Delete all widgets in each entry's layout.
    foreach (QHBoxLayout * entry, statEntries)
    {
        while ((child = entry->takeAt(0)) != nullptr) {
            delete child->widget(); // delete the widget
            delete child;   // delete the layout item
        }

    }

    statEntries.clear();
    // Delete all layouts in the stats layout.
    while ((child = ui->statsLayout->takeAt(0)) != nullptr) {
        delete child->widget(); // delete the widget
        delete child;   // delete the layout item
    }
}

void InfoDialog::populateStatsLayout(Cocktail &drink)
{
    // Add all the stats from the cocktail.
    QMap<QString, QString> statMap = drink.getStats();

    int insertIndex = 0;

    foreach (QString key, statMap.keys())
    {
        QLabel *categoryName = new QLabel();
        categoryName->setText(key);
        categoryName->setStyleSheet("font-weight: bold;");

        QLabel *categoryStats = new QLabel();
        categoryStats->setText(statMap[key]);

        QHBoxLayout *statEntry = new QHBoxLayout();
        statEntry->addWidget(categoryName);
        statEntry->addWidget(categoryStats);

        // Add it to this vector so that memory can be properly managed.
        statEntries.append(statEntry);

        ui->statsLayout->insertLayout(insertIndex, statEntry);
        insertIndex++;
    }
}
