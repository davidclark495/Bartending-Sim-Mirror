#ifndef BOX2DDIALOG_H
#define BOX2DDIALOG_H
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
 *  Style Checked by : David McLean - u0145629
 **/
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
    void box2dClosedSignal();

public slots:
    void startAnimation(int level);

private:
    Ui::Box2dDialog *ui;
    CocktailWidget* cocktailWidget;

    void endAnimation();

private slots:
    void on_buttonBox_accepted(); // if the user presses OK, end the animation as usual.
    void reject(); // if the window is closed, end the animation as usual.

};

#endif // BOX2DDIALOG_H
