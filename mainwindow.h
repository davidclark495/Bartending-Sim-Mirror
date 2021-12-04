#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include <QToolButton>
#include <QButtonGroup>
#include <QPropertyAnimation>
#include <infodialog.h>

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
    void on_groupBox_clicked();
    void bottleClicked(QAbstractButton *);
    void bottleReleased(QAbstractButton *);

    void on_shakerButton_released();

    void on_referenceButton_clicked();

private:
    Ui::MainWindow *ui;
    QButtonGroup bottles;
    QVector<QLabel*> barBottles;
    QPropertyAnimation *bottleTranslation;
    QPropertyAnimation *bottleScale;
    QPropertyAnimation *iconScale;
    InfoDialog* info;

};
#endif // MAINWINDOW_H
