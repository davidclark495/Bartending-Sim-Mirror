#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include <QToolButton>
#include <QButtonGroup>
#include <QRect>
#include <QPropertyAnimation>
#include <infodialog.h>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void shelfBottleClicked(QAbstractButton *);
    void barBottleClicked(QAbstractButton *);
    void bottleReleased(QAbstractButton *);

    void on_shakerButton_released();

    void on_referenceButton_clicked();
signals:
    void enterReferenceMode();

private:
    Ui::MainWindow *ui;
    Model *model;
    int barBottleCount;
    QButtonGroup shelfBottlesGroup;
    QButtonGroup barBottlesGroup;
    QButtonGroup barMixersGroup;
    QButtonGroup shelfMixersGroup;
    QVector<QLabel*> barBottlePositions;
    QVector<QLabel*> barMixerPositions;
    QMap<QAbstractButton *, QRect> bottleDefaultPosition;
    QMap<QAbstractButton *, QSize> bottleDefaultSize;
    QMap<QAbstractButton *, QSize> bottleDefaultIconSize;
    QPropertyAnimation *bottleTranslation;
    QPropertyAnimation *bottleScale;
    QPropertyAnimation *iconScale;
    InfoDialog* info;

};
#endif // MAINWINDOW_H
