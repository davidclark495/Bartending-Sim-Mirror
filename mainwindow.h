#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include <QToolButton>
#include <QButtonGroup>
#include <QPropertyAnimation>

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

private:
    Ui::MainWindow *ui;
    QButtonGroup bottles;
    QVector<QLabel*> barBottles;
    QPropertyAnimation *bottleTranslation;
    QPropertyAnimation *bottleScale;
    QPropertyAnimation *iconScale;

};
#endif // MAINWINDOW_H
