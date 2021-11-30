#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clickablelabel.h"
#include <QObject>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clickableLabel test;
    QObject* obj = &test;
    obj->setProperty("ingredientType", "bourbon");
    QPushButton scotchBottle;
    scotchBottle.setIcon(QIcon(":/Images/ScotchImage.png"));
    scotchBottle.setIconSize(QSize(65, 65));
    //bottles.push_back(scotchBottle);

    scotchBottle.show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

