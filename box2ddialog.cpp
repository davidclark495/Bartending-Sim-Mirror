#include "box2ddialog.h"
#include "ui_box2ddialog.h"
#include "cocktailwidget.h"
#include <QTimer>

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

void Box2dDialog::startAnimation(){
    this->show();
    cocktailWidget = new CocktailWidget(this);
    ui->gridLayout->addWidget(cocktailWidget);

    QTimer::singleShot(12000, this, &Box2dDialog::endAnimation);
}

void Box2dDialog::endAnimation(){
    ui->gridLayout->removeWidget(cocktailWidget);
    delete cocktailWidget;
    this->hide();
}
