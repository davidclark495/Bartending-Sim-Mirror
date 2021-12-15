#ifndef BOX2DDIALOG_H
#define BOX2DDIALOG_H

#include <QDialog>
#include "cocktailwidget.h"

namespace Ui {
class Box2dDialog;
}

class Box2dDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Box2dDialog(QWidget *parent = nullptr);
    ~Box2dDialog();

signals:
    void animationFinished();

public slots:
    void startAnimation();


private:
    Ui::Box2dDialog *ui;
    CocktailWidget* cocktailWidget;


private slots:
    void endAnimation();

};

#endif // BOX2DDIALOG_H
