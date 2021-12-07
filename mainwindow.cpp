#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clickablelabel.h"
#include <QObject>
#include <QVector>
#include <QToolButton>
#include <QPropertyAnimation>
#include <infodialog.h>
#include "model.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    info = new InfoDialog(this);
    model = new Model();
    barBottleCount = 0;

    shelfBottlesGroup.addButton(ui->bourbonButton);
    shelfBottlesGroup.addButton(ui->campariButton);
    shelfBottlesGroup.addButton(ui->ryeButton);
    shelfBottlesGroup.addButton(ui->vodkaButton);
    shelfBottlesGroup.addButton(ui->champagneButton);
    shelfBottlesGroup.addButton(ui->citrusVodkaButton);
    shelfBottlesGroup.addButton(ui->cognacButton);
    shelfBottlesGroup.addButton(ui->cointreauButton);
    shelfBottlesGroup.addButton(ui->darkTequilaButton);
    shelfBottlesGroup.addButton(ui->dryVermouthButton);
    shelfBottlesGroup.addButton(ui->grandMarnierButton);
    shelfBottlesGroup.addButton(ui->ginButton);
    shelfBottlesGroup.addButton(ui->lightRumButton);
    shelfBottlesGroup.addButton(ui->darkRumButton);
    shelfBottlesGroup.addButton(ui->midoriButton);
    shelfBottlesGroup.addButton(ui->peachSchnappsButton);
    shelfBottlesGroup.addButton(ui->silverTequilaButton);
    shelfBottlesGroup.addButton(ui->sweetVermouthButton);
    shelfBottlesGroup.addButton(ui->trippleSecButton);
    shelfBottlesGroup.addButton(ui->scotchButton);

    foreach(QAbstractButton *button, shelfBottlesGroup.buttons()) {
        button->setToolTip(button->text());
        bottleDefaultPosition[button] = button->geometry();
        bottleDefaultSize[button] = button->size();
        bottleDefaultIconSize[button] = button->iconSize();
    }

    barBottlePositions.append(ui->barBottle1);
    barBottlePositions.append(ui->barBottle2);
    barBottlePositions.append(ui->barBottle3);

    barMixerPositions.append(ui->barMixer1);
    barMixerPositions.append(ui->barMixer2);

    //For clicks on bottle buttons on shelf
    connect(&shelfBottlesGroup, &QButtonGroup::buttonPressed, this, &MainWindow::shelfBottleClicked);
    connect(&shelfBottlesGroup, &QButtonGroup::buttonReleased, this, &MainWindow::bottleReleased);

    //For clicks on bottle buttons on the bar
    connect(&barBottlesGroup, &QButtonGroup::buttonPressed, this, &MainWindow::barBottleClicked);
    connect(&barBottlesGroup, &QButtonGroup::buttonReleased, this, &MainWindow::bottleReleased);

    //For clicks on mixers on the shelf
    connect(&shelfBottlesGroup, &QButtonGroup::buttonPressed, this, &MainWindow::shelfBottleClicked);
    connect(&shelfBottlesGroup, &QButtonGroup::buttonReleased, this, &MainWindow::bottleReleased);

    //For clicks on bottle buttons on the bar
    connect(&barBottlesGroup, &QButtonGroup::buttonPressed, this, &MainWindow::barBottleClicked);
    connect(&barBottlesGroup, &QButtonGroup::buttonReleased, this, &MainWindow::bottleReleased);




    // Main Window -> Model Connections
    connect(this, &MainWindow::enterReferenceMode, model, &Model::startReferenceMode);

    // Info Window -> Model Connections
    connect(model, &Model::display_CocktailMap, info, &InfoDialog::displayCocktails);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::shelfBottleClicked(QAbstractButton* button)
{
    //We don't want to place more bottles on the bar than we have places.
    if(barBottleCount >= barBottlePositions.length())
        return;

    button->raise();  //Bring the bottle to the front of the widget stack
    button->setText("");

    QLabel *barBottleSpot = barBottlePositions.first();
    barBottlePositions.pop_front();
    barBottleCount++;

    bottleTranslation = new QPropertyAnimation(button, "geometry");
    bottleTranslation->setDuration(1000);
    bottleTranslation->setStartValue(button->geometry());
    bottleTranslation->setEndValue(barBottleSpot->geometry());
    bottleTranslation->start();
    bottleTranslation->start(QPropertyAnimation::DeleteWhenStopped);

    QSize bottleSize(barBottleSpot->size());
    bottleScale = new QPropertyAnimation(button, "size");
    bottleScale->setDuration(1000);
    bottleScale->setEndValue(bottleSize);
    bottleScale->start(QPropertyAnimation::DeleteWhenStopped);

    iconScale = new QPropertyAnimation(button, "iconSize");
    iconScale->setDuration(1000);
    iconScale->setEndValue(bottleSize);
    iconScale->start(QPropertyAnimation::DeleteWhenStopped);

    QApplication::setOverrideCursor(Qt::ClosedHandCursor);
    barBottlePositions.append(barBottleSpot);
    shelfBottlesGroup.removeButton(button);
    barBottlesGroup.addButton(button);
}
void MainWindow::barBottleClicked(QAbstractButton* button)
{
    button->setText(button->toolTip());

    bottleTranslation = new QPropertyAnimation(button, "geometry");
    bottleTranslation->setDuration(1000);
    bottleTranslation->setStartValue(button->geometry());
    bottleTranslation->setEndValue(bottleDefaultPosition[button]);
    bottleTranslation->start();
    bottleTranslation->start(QPropertyAnimation::DeleteWhenStopped);

    bottleScale = new QPropertyAnimation(button, "size");
    bottleScale->setDuration(1000);
    bottleScale->setEndValue(bottleDefaultSize[button]);
    bottleScale->start(QPropertyAnimation::DeleteWhenStopped);

    iconScale = new QPropertyAnimation(button, "iconSize");
    iconScale->setDuration(1000);
    iconScale->setEndValue(bottleDefaultIconSize[button]);
    iconScale->start(QPropertyAnimation::DeleteWhenStopped);

    shelfBottlesGroup.addButton(button);
    barBottleCount--;
}

void MainWindow::bottleReleased(QAbstractButton* button)
{
    QApplication::restoreOverrideCursor();
}


void MainWindow::on_shakerButton_released()
{
    QApplication::restoreOverrideCursor();
    foreach(QAbstractButton *button, barBottlesGroup.buttons()) {
        barBottleClicked(button);
    }
}


void MainWindow::on_referenceButton_clicked()
{
    info->show();
    emit enterReferenceMode();
}

