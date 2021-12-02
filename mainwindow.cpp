#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clickablelabel.h"
#include <QObject>
#include <QToolButton>
#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bottles.addButton(ui->bourbonButton);
    bottles.addButton(ui->campariButton);
    bottles.addButton(ui->ryeButton);
    bottles.addButton(ui->vodkaButton);
    bottles.addButton(ui->champagneButton);
    bottles.addButton(ui->citrusVodkaButton);
    bottles.addButton(ui->cognacButton);
    bottles.addButton(ui->cointreauButton);
    bottles.addButton(ui->darkTequilaButton);
    bottles.addButton(ui->dryVermouthButton);
    bottles.addButton(ui->grandMarnierButton);
    bottles.addButton(ui->ginButton);
    bottles.addButton(ui->lightRumButton);
    bottles.addButton(ui->darkRumButton);
    bottles.addButton(ui->midoriButton);
    bottles.addButton(ui->peachSchnappsButton);
    bottles.addButton(ui->silverTequilaButton);
    bottles.addButton(ui->sweetVermouthButton);
    bottles.addButton(ui->trippleSecButton);
    bottles.addButton(ui->scotchButton);

    connect(&bottles, &QButtonGroup::buttonPressed, this, &MainWindow::bottleClicked);
    connect(&bottles, &QButtonGroup::buttonReleased, this, &MainWindow::bottleReleased);

    //bottleAnimation = new QPropertyAnimation(ui->bourbonButton, "geometry");
    //bottleAnimation->setDuration(2000);
    //bottleAnimation->setStartValue(ui->bourbonButton->geometry());
    //bottleAnimation->setEndValue(ui->bottle1Label->geometry());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_bourbonButton_pressed()
{
}

void MainWindow::bottleClicked(QAbstractButton* button)
{
    button->setText("");
    bottleTranslation = new QPropertyAnimation(button, "geometry");
    bottleTranslation->setDuration(1000);
    bottleTranslation->setStartValue(button->geometry());
    bottleTranslation->setEndValue(ui->bottle1Label->geometry());
    bottleTranslation->start();
    bottleTranslation->start(QPropertyAnimation::DeleteWhenStopped);

    QSize bottleSize(ui->bottle1Label->size());
    bottleScale = new QPropertyAnimation(button, "size");
    bottleScale->setDuration(1000);
    bottleScale->setEndValue(bottleSize);
    bottleScale->start(QPropertyAnimation::DeleteWhenStopped);

    iconScale = new QPropertyAnimation(button, "iconSize");
    iconScale->setDuration(1000);
    iconScale->setEndValue(bottleSize);
    iconScale->start(QPropertyAnimation::DeleteWhenStopped);

    QApplication::setOverrideCursor(Qt::ClosedHandCursor);
}

void MainWindow::bottleReleased(QAbstractButton* button)
{
    QApplication::restoreOverrideCursor();
}

void MainWindow::on_bourbonButton_clicked()
{

}


void MainWindow::on_bourbonButton_released()
{
}


void MainWindow::on_groupBox_clicked()
{

}


void MainWindow::on_shakerButton_released()
{
    ui->setupUi(this);
}

