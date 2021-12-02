#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clickablelabel.h"
#include <QObject>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clickableLabel test;
    QObject* obj = &test;
    obj->setProperty("ingredientType", "bourbon");



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
    bottles.addButton(ui->midoriButton);
    bottles.addButton(ui->peachSchnappsButton);
    bottles.addButton(ui->silverTequilaButton);
    bottles.addButton(ui->sweetVermouthButton);
    bottles.addButton(ui->trippleSecButton);
    bottles.addButton(ui->scotchButton);

    connect(&bottles, &QButtonGroup::buttonPressed, this, &MainWindow::bottleClicked);
    connect(&bottles, &QButtonGroup::buttonReleased, this, &MainWindow::bottleReleased);
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

