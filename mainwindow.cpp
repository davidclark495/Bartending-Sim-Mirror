#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clickablelabel.h"
#include <QObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clickableLabel test;
    QObject* obj = &test;
    obj->setProperty("ingredientType", "bourbon");
}

MainWindow::~MainWindow()
{
    delete ui;
}

