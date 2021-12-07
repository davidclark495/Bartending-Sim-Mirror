#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clickablelabel.h"
#include <QObject>
#include <QVector>
#include <QToolButton>
#include <QPropertyAnimation>
#include <QTime>
#include <infodialog.h>
#include <iostream>
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


    allButtonGroups.append(&shelfBottlesGroup);
    allButtonGroups.append(&shelfMixersGroup);
    allButtonGroups.append(&shelfGarnishGroup);
    allButtonGroups.append(&shelfGlassGroup);

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

    ui->learnButton->raise();
    ui->quizButton->raise();


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
    connect(this, &MainWindow::learnSignal, model, &Model::startLearningMode);
    connect(this, &MainWindow::quizSignal, model, &Model::startQuizMode);

    // Info Window -> Model Connections
    connect(model, &Model::displayCocktailMap, info, &InfoDialog::displayCocktails);
    connect(model, &Model::displayCocktail, this, &MainWindow::displayCocktail);
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
    if (currentMode == learn)
        emit learnSignal();
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

void MainWindow::on_learnButton_clicked(bool checked)
{
    currentMode = learn;
    ui->learnButton->hide();
    ui->quizButton->hide();
    emit learnSignal();

}


void MainWindow::on_quizButton_clicked(bool checked)
{
    currentMode = quiz;
    ui->learnButton->hide();
    ui->quizButton->hide();
    emit quizSignal();

}

void MainWindow::displayCocktail(Cocktail currentCocktail)
{
    writeMessage("Today's Special:");
    delay(200);
    writeMessage(currentCocktail.getName());
    delay(1000);
    foreach (QString ingredientName, currentCocktail.getIngredientsMap().keys())
    {
        QString ingredientString = ingredientName;
        findButton(ingredientName);
        ingredientString.append(":  ");
        ingredientString.append(QString::number(currentCocktail.getIngredientsMap()[ingredientName]));
        ingredientString.append(" oz");
        writeMessage(ingredientString );
        delay(1000);
    }
    QString iceString = ("Serve ");
    if (currentCocktail.getIce() == "Rocks")
        iceString.append("On the Rocks");
    else
        iceString.append(currentCocktail.getIce());
    writeMessage(iceString);
    delay(1000);

    QString glassString = "in a ";
    glassString.append(currentCocktail.getGlass());
    glassString.append(" glass");
    findButton(currentCocktail.getGlass());
    writeMessage(glassString);
    delay(1000);

    QString garnishString = currentCocktail.getGarnish();
    findButton(garnishString);
    writeMessage("Garnish with: ");
    delay(1000);
    findButton(garnishString);
    writeMessage(garnishString);
    delay(1000);
}

void MainWindow::writeMessage(QString message)
{
    QString builderString = "";
    for (QChar c : message)
    {
        builderString.append(c);
        ui->chalkboardText->setText(builderString);
        delay(chalkboardDelay);
    }

}

void MainWindow::delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

void MainWindow::findButton(QString text)
{
    std::cout << "Searching for Button: " << text.toStdString() << std::endl;
    foreach (QAbstractButton *button, shelfBottlesGroup.buttons()){
        if(button->toolTip().contains(text)) {
            shelfBottleClicked(button);
            return;
        }
    }
    foreach (QAbstractButton *button, shelfMixersGroup.buttons()){
        if(button->toolTip().contains(text)) {
            shelfMixerClicked(button);
            return;
        }
    }
    foreach (QAbstractButton *button, shelfGarnishGroup.buttons()){
        if(text.contains(button->toolTip())) {
            shelfGarnishClicked(button);
            return;
        }
    }
    foreach (QAbstractButton *button, shelfGlassGroup.buttons()){
        if(text.contains(button->toolTip())) {
            shelfGlassClicked(button);
            return;
        }
    }
}
