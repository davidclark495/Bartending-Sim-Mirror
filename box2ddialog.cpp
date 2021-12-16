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
#include <QTimer>
#include <QString>
#include "box2ddialog.h"
#include "ui_box2ddialog.h"
#include "cocktailwidget.h"

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

void Box2dDialog::startAnimation(int level) {
    this->show();
    cocktailWidget = new CocktailWidget(this);
    ui->gridLayout->addWidget(cocktailWidget);
    ui->userMessage->setText("Congratulations!  You have been promoted to:");
    ui->userRank->setText("Level " + QString::number(level) + " Bartender");
}

void Box2dDialog::endAnimation() {
    ui->gridLayout->removeWidget(cocktailWidget);
    delete cocktailWidget;
    this->hide();
    emit box2dClosedSignal();
}

// If the user presses OK, end the animation as usual.
void Box2dDialog::on_buttonBox_accepted() {
    endAnimation();
}

// If the window is closed, end the animation as usual.
void Box2dDialog::reject() {
    endAnimation();
}
