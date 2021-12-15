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
    void box2dClosedSignal();

public slots:
    void startAnimation(int level);


private:
    Ui::Box2dDialog *ui;
    CocktailWidget* cocktailWidget;


private slots:
    void endAnimation();

    void on_buttonBox_accepted();
};

#endif // BOX2DDIALOG_H
