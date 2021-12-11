#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QVector>
#include <QToolButton>
#include <QPropertyAnimation>
#include <QTime>
#include <QFont>
#include <QInputDialog>
#include <QMessageBox>
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

    garnishOptions[ui->orangeButton->toolTip()] =  QStringList({ "Orange Twist", "Orange Slice", "Orange Wedge" });
    garnishOptions[ui->lemonButton->toolTip()] =  QStringList({ "Lemon Twist", "Lemon Slice", "Lemon Wedge" });
    garnishOptions[ui->limeButton->toolTip()] =  QStringList({ "Lime Twist", "Lime Slice", "Lime Wedge" });

    iceOptions = QStringList({ "Rocks", "Neat", "Straight Up" });

    defaultChalkboardFont = ui->chalkboardText->font();

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
    shelfGarnishGroup.addButton(ui->mintButton);

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

    //For clicks on mixers on the shelf
    connect(&shelfMixersGroup, &QButtonGroup::buttonPressed, this, &MainWindow::shelfMixerClicked);

    //For clicks on garnish buttons on shelf
    connect(&shelfGarnishGroup, &QButtonGroup::buttonPressed, this, &MainWindow::shelfGarnishClicked);

    //For clicks on glass on the shelf
    connect(&shelfGlassGroup, &QButtonGroup::buttonPressed, this, &MainWindow::shelfGlassClicked);


    ////////////////////// //
    /// Bar Connections //
    //////////////////// //
    //For clicks on bottle buttons on the bar
    connect(&barBottlesGroup, &QButtonGroup::buttonPressed, this, &MainWindow::barBottleClicked);

    //For clicks on mixers buttons on the bar
    connect(&barMixersGroup, &QButtonGroup::buttonPressed, this, &MainWindow::barMixerClicked);

    //For clicks on bottle buttons on the bar
    connect(&barGarnishGroup, &QButtonGroup::buttonPressed, this, &MainWindow::barGarnishClicked);

    //For clicks on mixers buttons on the bar
    connect(&barGlassGroup, &QButtonGroup::buttonPressed, this, &MainWindow::barGlassClicked);

    // Main Window -> Model Connections
    connect(this, &MainWindow::enterReferenceMode, model, &Model::startReferenceMode);
    connect(this, &MainWindow::learnSignal, model, &Model::startLearningMode);
    connect(this, &MainWindow::quizSignal, model, &Model::startQuizMode);
    connect(this, &MainWindow::submitCocktail, model, &Model::evaluateCocktail);

    // Model Connections -> Main Window Connections
    connect(model, &Model::sendNextCocktailLearning, this, &MainWindow::displayCocktail);
    connect(model, &Model::sendNextCocktailQuiz, this, &MainWindow::quizCocktail);
    connect(model, &Model::sendCocktailResult, this, &MainWindow::displayQuizResult);

    // Model Connections -> Info Window Connections
    connect(model, &Model::sendAllCocktailsReference, info, &InfoDialog::displayCocktails);

}

MainWindow::~MainWindow()
{
    delete ui;
}

///////////////////////// //
/// Shelf Button Clicked //
/////////////////////// //

void MainWindow::shelfBottleClicked(QAbstractButton* button)
{
    if ( barBottleCount >= barBottlePositions.length() )
        return;

    bool ok;
    double d = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"),
                                       tr("Amount:"), 1.0, -10000, 10000, 2, &ok,
                                       Qt::WindowFlags(), 1);
    if (ok) {
        ingredientVolumes[button->toolTip()] = d;
        moveButtonToBar(button, shelfBottlesGroup, barBottlesGroup, barBottleCount, barBottlePositions);
    }

}

void MainWindow::shelfMixerClicked(QAbstractButton* button)
{
    if ( barMixerCount >= barMixerPositions.length() )
        return;

    bool ok;
    double d = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"),
                                       tr("Amount:"), 1.0, -10000, 10000, 2, &ok,
                                       Qt::WindowFlags(), 1);
    if (ok) {
        ingredientVolumes[button->toolTip()] = d;
        moveButtonToBar(button, shelfMixersGroup, barMixersGroup, barMixerCount, barMixerPositions);
    }
}

void MainWindow::shelfGarnishClicked(QAbstractButton* button)
{
    if ( barGarnishCount >= barGarnishPositions.length() )
        return;

    bool ok = true;
    if (garnishOptions.contains(button->toolTip())) {
        QString item = QInputDialog::getItem(this, tr("QInputDialog::Garnish()"),
                                            tr("Type Of Garnish:"), garnishOptions[button->toolTip()], 0, false, &ok);
        if (ok && !item.isEmpty()) {
            garnishSelection.insert(item);
            moveButtonToBar(button, shelfGarnishGroup, barGarnishGroup, barGarnishCount, barGarnishPositions);
        }
    }
    else {
        moveButtonToBar(button, shelfGarnishGroup, barGarnishGroup, barGarnishCount, barGarnishPositions);
    }
}

void MainWindow::shelfGlassClicked(QAbstractButton* button)
{
    moveButtonToBar(button, shelfGlassGroup, barGlassGroup, barGlassCount, barGlassPositions);
    glassSelection = button->toolTip();
}

///////////////////////// //
/// Bar Button Clicked   //
/////////////////////// //
void MainWindow::barBottleClicked(QAbstractButton* button)
{
    button->setText(button->toolTip());
    moveButtonToShelf(button, shelfBottlesGroup, barBottleCount);
    ingredientVolumes.remove(button->toolTip());
}

void MainWindow::barMixerClicked(QAbstractButton* button)
{
    moveButtonToShelf(button, shelfMixersGroup, barMixerCount);
    ingredientVolumes.remove(button->toolTip());
}

void MainWindow::barGarnishClicked(QAbstractButton* button)
{
    moveButtonToShelf(button, shelfGarnishGroup, barGarnishCount);
    garnishSelection.remove(button->toolTip());
}

void MainWindow::barGlassClicked(QAbstractButton* button)
{
    moveButtonToShelf(button, shelfGlassGroup, barGlassCount);
    glassSelection = "";
}


/////////////////////// //
/// Button Animations  //
///////////////////// //

void MainWindow::moveButtonToBar(QAbstractButton * button, QButtonGroup &shelfGroup, QButtonGroup &barGroup, int &count, QVector<QLabel*> &barPositions)
{
    //We don't want to place more buttons on the bar than we have places.
    if(count >= barPositions.length())
        return;

    if (currentMode == quiz)
    {
        QApplication::setOverrideCursor(Qt::ClosedHandCursor);
        delay(200);
        QApplication::restoreOverrideCursor();
    }
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

    barPositions.append(barButtonSpot);

    shelfGroup.removeButton(button);
    barGroup.addButton(button);
}

void MainWindow::moveButtonToShelf(QAbstractButton *button, QButtonGroup &group, int &count)
{
    if (currentMode == quiz)
    {
        QApplication::setOverrideCursor(Qt::ClosedHandCursor);
        delay(200);
        QApplication::restoreOverrideCursor();
    }
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

void MainWindow::on_iceBucketButton_clicked()
{
    bool ok = true;
    QString item = QInputDialog::getItem(this, tr("Ice Options"),
                                            tr("Type of ice:"), iceOptions, 0, false, &ok);
        if (ok && !item.isEmpty()) {
           iceSelection = item;
        }
}

void MainWindow::on_shakerButton_clicked()
{
    clearBar();
    if (currentMode == learn)
        emit learnSignal();
    if (currentMode == quiz)
    {
        currentCocktail = Cocktail(glassSelection, iceSelection, ingredientVolumes, garnishSelection);
        emit submitCocktail(&currentCocktail);
    }
}

void MainWindow::clearBar()
{
    foreach (QAbstractButton *button, barBottlesGroup.buttons()) {
        moveButtonToShelf(button, shelfBottlesGroup, barBottleCount);
    }

    foreach (QAbstractButton *button, barMixersGroup.buttons()) {
        moveButtonToShelf(button, shelfMixersGroup, barMixerCount);
    }

    foreach (QAbstractButton *button, barGarnishGroup.buttons()) {
        moveButtonToShelf(button, shelfGarnishGroup, barGarnishCount);
    }

    foreach (QAbstractButton *button, barGlassGroup.buttons()) {
        moveButtonToShelf(button, shelfGlassGroup, barGlassCount);
    }

}

void MainWindow::on_referenceButton_clicked()
{
    info->show();
    emit enterReferenceMode();
}

void MainWindow::on_learnButton_clicked()
{
    currentMode = learn;
    ui->learnButton->hide();
    ui->quizButton->hide();
    disableButtons();
    emit learnSignal();

}

void MainWindow::on_quizButton_clicked()
{
    currentMode = quiz;
    ui->learnButton->hide();
    ui->quizButton->hide();
    emit quizSignal();

}

void MainWindow::quizCocktail(Cocktail currentCocktail)
{
    writeMessage("Next Order:");
    delay(200);
    writeMessage(currentCocktail.getName());
    delay(1000);
}

//Displays a give cocktails ingredients on the bar,
//and writes the information about the component on the
//chalkboard.
void MainWindow::displayCocktail(Cocktail currentCocktail)
{
    //Want to disable the shaker button, but not grey out the image
    fancyDisable(ui->shakerButton);

    writeMessage("Today's Special:");
    delay(200);
    writeMessage(currentCocktail.getName());
    delay(1000);
    foreach (QString ingredientName, currentCocktail.getIngredientsMap().keys())
    {
        if (currentMode == home)  //We don't want to move things around after the exit button is clicked
            return;
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
    delay(500);

    QString glassString = "in a ";
    glassString.append(currentCocktail.getGlass());
    glassString.append(" glass");
    findButton(currentCocktail.getGlass());
    writeMessage(glassString);
    delay(1000);

    foreach (QString garnishString, currentCocktail.getGarnishSet()){
        writeMessage("Garnish with: ");
        findButton(garnishString);
        delay(500);
        writeMessage(garnishString);
    }
    delay(1000);
    writeMessage(currentCocktail.getName());
    ui->shakerButton->setEnabled(true);
}

void MainWindow::displayQuizResult(bool result)
{
    QString resultTitle;
    QString resultString;
    if (result)
    {
        resultTitle = "Success";
        resultString = "Solid work!";
    }
    else
    {
        resultTitle = "Failure";
        resultString = "Better luck next time";
    }

    QMessageBox::information(this, resultTitle, resultString );
    emit quizSignal();
}

//Writes a message on the chalkbaord using a global variable to set a delay
//as the letters are written.
void MainWindow::writeMessage(QString message)
{

    if (currentMode == home)  //We don't want to write things around after the exit button is clicked
        return;
    ui->chalkboardText->setFont(defaultChalkboardFont);
    if (message.length() > 20) {
        QFont newFont = defaultChalkboardFont;
        newFont.setPointSize(16);
        ui->chalkboardText->setFont(newFont);
    }
    QString builderString = "";
    for (QChar c : message)
    {
        builderString.append(c);
        ui->chalkboardText->setText(builderString);
        delay(chalkboardDelay);
    }
}

//Used to insert a pause in a block of code and not lock up the UI.
void MainWindow::delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

//Look through all the button groups and find a specific button,
//then fire it's cliked event to move the button.
void MainWindow::findButton(QString text)
{
    std::cout << "Searching for Button: " << text.toStdString() << std::endl;
    foreach (QAbstractButton *button, shelfBottlesGroup.buttons()){
        if(button->toolTip().contains(text)) {
            moveButtonToBar(button, shelfBottlesGroup, barBottlesGroup, barBottleCount, barBottlePositions);

            return;
        }
    }
    foreach (QAbstractButton *button, shelfMixersGroup.buttons()){
        if(button->toolTip().contains(text)) {
            moveButtonToBar(button, shelfMixersGroup, barMixersGroup, barMixerCount, barMixerPositions);
            return;
        }
    }
    foreach (QAbstractButton *button, shelfGarnishGroup.buttons()){
        if(text.contains(button->toolTip())) {
            moveButtonToBar(button, shelfGarnishGroup, barGarnishGroup, barGarnishCount, barGarnishPositions);
            return;
        }
    }
    foreach (QAbstractButton *button, shelfGlassGroup.buttons()){
        if(text.contains(button->toolTip())) {
            moveButtonToBar(button, shelfGlassGroup, barGlassGroup, barGlassCount, barGlassPositions);
            return;
        }
    }
}

//Disable all the buttons on the screen.
void MainWindow::disableButtons()
{
    foreach (QButtonGroup *group, allButtonGroups) {
        foreach (QAbstractButton *button, group->buttons()) {
            fancyDisable(button);
        }
    }
}

//Basically a work around to disable buttons without greying them out.
//We rely on the mouse cursor to let the user know the button is disabled.
void MainWindow::fancyDisable(QAbstractButton * button)
{
    QIcon icon;
    icon.addPixmap(button->icon().pixmap(200), QIcon::Normal);
    icon.addPixmap(button->icon().pixmap(200), QIcon::Disabled);
    button->setIcon(icon);
    button->setEnabled(false);
}

void MainWindow::on_ExitButton_clicked()
{
    currentMode = home;
    clearBar();
    disableButtons();
    delay(50);
    ui->learnButton->show();
    ui->quizButton->show();
    ui->learnButton->raise();
    ui->quizButton->raise();
}

