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
#include "box2ddialog.h"
#include "ui_box2ddialog.h"
#include "cocktailwidget.h"
#include <QTimer>
#include <QString>

Box2dDialog::Box2dDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Box2dDialog)
{
    ui->setupUi(this);
}

Box2dDialog::~Box2dDialog()
{
    delete ui;
    delete cocktailWidget;
}

void Box2dDialog::startAnimation(int level){
    this->show();
    cocktailWidget = new CocktailWidget(this);
    ui->gridLayout->addWidget(cocktailWidget);
    ui->userMessage->setText("Congratulations!  You have been promoted to level " + QString::number(level));
}

void Box2dDialog::endAnimation(){
    ui->gridLayout->removeWidget(cocktailWidget);
    delete cocktailWidget;
    this->hide();
    emit box2dClosedSignal();
}

void Box2dDialog::on_buttonBox_accepted()
{
    endAnimation();
}

