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
    barMixerCount = 0;
    barGarnishCount = 0;
    barGlassCount = 0;

    ui->bottle1Amount->hide();
    ui->bottle2Amount->hide();
    ui->bottle3Amount->hide();

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

    shelfMixersGroup.addButton(ui->orangeJuiceButton);
    shelfMixersGroup.addButton(ui->lemonJuiceButton);
    shelfMixersGroup.addButton(ui->limeJuiceButton);
    shelfMixersGroup.addButton(ui->cranberryJuiceButton);
    shelfMixersGroup.addButton(ui->bitterButton);
    shelfMixersGroup.addButton(ui->sugarButton);

    shelfGarnishGroup.addButton(ui->orangeButton);
    shelfGarnishGroup.addButton(ui->limeButton);
    shelfGarnishGroup.addButton(ui->lemonButton);
    shelfGarnishGroup.addButton(ui->cherryButton);
    shelfGarnishGroup.addButton(ui->eggButton);
    shelfGarnishGroup.addButton(ui->oliveButton);

    shelfGlassGroup.addButton(ui->cocktailGlassButton);
    shelfGlassGroup.addButton(ui->highballButton);
    shelfGlassGroup.addButton(ui->tumblerButton);
    shelfGlassGroup.addButton(ui->copperCupButton);
    shelfGlassGroup.addButton(ui->fluteButton);

    foreach (QAbstractButton *button, shelfBottlesGroup.buttons()) {
        button->setToolTip(button->text());
        defaultButtonData[button] = buttonData(button);
    }

    foreach (QAbstractButton *button, shelfMixersGroup.buttons()) {
        defaultButtonData[button] = buttonData(button);
    }

    foreach (QAbstractButton *button, shelfGarnishGroup.buttons()) {
        defaultButtonData[button] = buttonData(button);
    }

    foreach (QAbstractButton *button, shelfGlassGroup.buttons()) {
        defaultButtonData[button] = buttonData(button);
    }

    barBottlePositions.append(ui->barBottle1);
    barBottlePositions.append(ui->barBottle2);
    barBottlePositions.append(ui->barBottle3);

    barMixerPositions.append(ui->barMixer1);
    barMixerPositions.append(ui->barMixer2);

    barGarnishPositions.append(ui->barGarnish1);
    barGarnishPositions.append(ui->barGarnish2);

    barGlassPositions.append(ui->barGlass);


    ////////////////////// //
    /// Shelf Connections //
    //////////////////// //
    //For clicks on bottle buttons on shelf
    connect(&shelfBottlesGroup, &QButtonGroup::buttonPressed, this, &MainWindow::shelfBottleClicked);
    connect(&shelfBottlesGroup, &QButtonGroup::buttonReleased, this, &MainWindow::buttonReleased);

    //For clicks on mixers on the shelf
    connect(&shelfMixersGroup, &QButtonGroup::buttonPressed, this, &MainWindow::shelfMixerClicked);
    connect(&shelfMixersGroup, &QButtonGroup::buttonReleased, this, &MainWindow::buttonReleased);

    //For clicks on garnish buttons on shelf
    connect(&shelfGarnishGroup, &QButtonGroup::buttonPressed, this, &MainWindow::shelfGarnishClicked);
    connect(&shelfGarnishGroup, &QButtonGroup::buttonReleased, this, &MainWindow::buttonReleased);

    //For clicks on glass on the shelf
    connect(&shelfGlassGroup, &QButtonGroup::buttonPressed, this, &MainWindow::shelfGlassClicked);
    connect(&shelfGlassGroup, &QButtonGroup::buttonReleased, this, &MainWindow::buttonReleased);


    ////////////////////// //
    /// Bar Connections //
    //////////////////// //

    //For clicks on bottle buttons on the bar
    connect(&barBottlesGroup, &QButtonGroup::buttonPressed, this, &MainWindow::barBottleClicked);
    connect(&barBottlesGroup, &QButtonGroup::buttonReleased, this, &MainWindow::buttonReleased);

    //For clicks on mixers buttons on the bar
    connect(&barMixersGroup, &QButtonGroup::buttonPressed, this, &MainWindow::barMixerClicked);
    connect(&barMixersGroup, &QButtonGroup::buttonReleased, this, &MainWindow::buttonReleased);

    //For clicks on bottle buttons on the bar
    connect(&barGarnishGroup, &QButtonGroup::buttonPressed, this, &MainWindow::barGarnishClicked);
    connect(&barGarnishGroup, &QButtonGroup::buttonReleased, this, &MainWindow::buttonReleased);

    //For clicks on mixers buttons on the bar
    connect(&barGlassGroup, &QButtonGroup::buttonPressed, this, &MainWindow::barGlassClicked);
    connect(&barGlassGroup, &QButtonGroup::buttonReleased, this, &MainWindow::buttonReleased);




    // Main Window -> Model Connections
    connect(this, &MainWindow::enterReferenceMode, model, &Model::startReferenceMode);

    // Info Window -> Model Connections
    connect(model, &Model::display_CocktailMap, info, &InfoDialog::displayCocktails);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_shakerButton_released()
{
    QApplication::restoreOverrideCursor();
    foreach (QAbstractButton *button, barBottlesGroup.buttons()) {
        barBottleClicked(button);
    }

    foreach (QAbstractButton *button, barMixersGroup.buttons()) {
        barMixerClicked(button);
    }

    foreach (QAbstractButton *button, barGarnishGroup.buttons()) {
        barGarnishClicked(button);
    }

    foreach (QAbstractButton *button, barGlassGroup.buttons()) {
        barGlassClicked(button);
    }
}


void MainWindow::on_referenceButton_clicked()
{
    info->show();
    emit enterReferenceMode();
}

void MainWindow::buttonReleased(QAbstractButton* button)
{
    QApplication::restoreOverrideCursor();
}

///////////////////////// //
/// Shelf Button Clicked //
/////////////////////// //

void MainWindow::shelfBottleClicked(QAbstractButton* button)
{
    moveButtonToBar(button, shelfBottlesGroup, barBottlesGroup, barBottleCount, barBottlePositions);
}

void MainWindow::shelfMixerClicked(QAbstractButton* button)
{
    moveButtonToBar(button, shelfMixersGroup, barMixersGroup, barMixerCount, barMixerPositions);
}

void MainWindow::shelfGarnishClicked(QAbstractButton* button)
{
    moveButtonToBar(button, shelfGarnishGroup, barGarnishGroup, barGarnishCount, barGarnishPositions);
}

void MainWindow::shelfGlassClicked(QAbstractButton* button)
{
    moveButtonToBar(button, shelfGlassGroup, barGlassGroup, barGlassCount, barGlassPositions);
}

///////////////////////// //
/// Bar Button Clicked   //
/////////////////////// //

void MainWindow::barBottleClicked(QAbstractButton* button)
{
    button->setText(button->toolTip());
    moveButtonToShelf(button, shelfBottlesGroup, barBottleCount);
}

void MainWindow::barMixerClicked(QAbstractButton* button)
{
    moveButtonToShelf(button, shelfMixersGroup, barMixerCount);
}

void MainWindow::barGarnishClicked(QAbstractButton* button)
{
    moveButtonToShelf(button, shelfGarnishGroup, barGarnishCount);
}

void MainWindow::barGlassClicked(QAbstractButton* button)
{
    moveButtonToShelf(button, shelfGlassGroup, barGlassCount);
}


/////////////////////// //
/// Button Animations  //
///////////////////// //

void MainWindow::moveButtonToBar(QAbstractButton * button, QButtonGroup &shelfGroup, QButtonGroup &barGroup, int &count, QVector<QLabel*> &barPositions)
{
    //We don't want to place more buttons on the bar than we have places.
    if(count >= barPositions.length())
        return;

    button->raise();  //Bring the button to the front of the widget stack
    button->setText("");

    QLabel *barButtonSpot = barPositions.first();
    barPositions.pop_front();
    count++;

    buttonTranslation = new QPropertyAnimation(button, "geometry");
    buttonTranslation->setDuration(700);
    buttonTranslation->setStartValue(button->geometry());
    buttonTranslation->setEndValue(barButtonSpot->geometry());
    buttonTranslation->start();
    buttonTranslation->start(QPropertyAnimation::DeleteWhenStopped);

    QSize bottleSize(barButtonSpot->size());
    buttonScale = new QPropertyAnimation(button, "size");
    buttonScale->setDuration(700);
    buttonScale->setEndValue(bottleSize);
    buttonScale->start(QPropertyAnimation::DeleteWhenStopped);

    buttonIconScale = new QPropertyAnimation(button, "iconSize");
    buttonIconScale->setDuration(700);
    buttonIconScale->setEndValue(bottleSize);
    buttonIconScale->start(QPropertyAnimation::DeleteWhenStopped);

    QApplication::setOverrideCursor(Qt::ClosedHandCursor);
    barPositions.append(barButtonSpot);

    shelfGroup.removeButton(button);
    barGroup.addButton(button);
}

void MainWindow::moveButtonToShelf(QAbstractButton *button, QButtonGroup &group, int &count)
{
    buttonTranslation = new QPropertyAnimation(button, "geometry");
    buttonTranslation->setDuration(700);
    buttonTranslation->setStartValue(button->geometry());
    buttonTranslation->setEndValue(defaultButtonData[button].getGeometry());
    buttonTranslation->start();
    buttonTranslation->start(QPropertyAnimation::DeleteWhenStopped);

    buttonScale = new QPropertyAnimation(button, "size");
    buttonScale->setDuration(700);
    buttonScale->setEndValue(defaultButtonData[button].getButtonSize());
    buttonScale->start(QPropertyAnimation::DeleteWhenStopped);

    buttonIconScale = new QPropertyAnimation(button, "iconSize");
    buttonIconScale->setDuration(700);
    buttonIconScale->setEndValue(defaultButtonData[button].getIconSize());
    buttonIconScale->start(QPropertyAnimation::DeleteWhenStopped);

    group.addButton(button);
    count--;
}





