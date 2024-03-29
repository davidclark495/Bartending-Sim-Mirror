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
#include "buttondata.h"

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
    void shelfMixerClicked(QAbstractButton *);
    void shelfGarnishClicked(QAbstractButton *);
    void shelfGlassClicked(QAbstractButton *);

    void barBottleClicked(QAbstractButton *);
    void barMixerClicked(QAbstractButton *);
    void barGarnishClicked(QAbstractButton *);
    void barGlassClicked(QAbstractButton *);

    void buttonReleased(QAbstractButton *);
    void on_shakerButton_released();
    void on_referenceButton_clicked();
    void on_learnButton_clicked(bool checked);
    void on_quizButton_clicked(bool checked);

    void displayCocktail(Cocktail);
    void quizCocktail(Cocktail);

signals:
    void enterReferenceMode();
    void learnSignal();
    void quizSignal();

private:
    Ui::MainWindow *ui;
    Model *model;
    int barBottleCount;
    int barMixerCount;
    int barGarnishCount;
    int barGlassCount;

    enum mode {
        learn,
        quiz
    };

    int chalkboardDelay = 100;

    mode currentMode;

    QButtonGroup shelfBottlesGroup;
    QButtonGroup shelfMixersGroup;
    QButtonGroup shelfGarnishGroup;
    QButtonGroup shelfGlassGroup;

    QButtonGroup barBottlesGroup;
    QButtonGroup barMixersGroup;
    QButtonGroup barGarnishGroup;
    QButtonGroup barGlassGroup;

    QVector<QLabel*> barBottlePositions;
    QVector<QLabel*> barMixerPositions;
    QVector<QLabel*> barGarnishPositions;
    QVector<QLabel*> barGlassPositions;
    QVector<QButtonGroup*> allButtonGroups;

    QMap<QAbstractButton *, buttonData> defaultButtonData;
    QPropertyAnimation *buttonTranslation;
    QPropertyAnimation *buttonScale;
    QPropertyAnimation *buttonIconScale;
    InfoDialog* info;

    void moveButtonToShelf(QAbstractButton * button, QButtonGroup &group, int &count);
    void moveButtonToBar(QAbstractButton * button, QButtonGroup &shelfGroup, QButtonGroup &barGroup, int &count, QVector<QLabel*> &barPositions);

    void findButton(QString text);
    void writeMessage(QString message);
    void delay( int millisecondsToWait );
};
#endif // MAINWINDOW_H
