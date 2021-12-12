#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include <QToolButton>
#include <QButtonGroup>
#include <QRect>
#include <QFont>
#include <QPropertyAnimation>
#include <QStringList>
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

    void on_referenceButton_clicked();
    void on_learnButton_clicked();
    void on_quizButton_clicked();
    void on_iceBucketButton_clicked();
    void on_shakerButton_clicked();
    void on_ExitButton_clicked();

    void displayCocktail(Cocktail);
    void quizCocktail(Cocktail);
    void displayQuizResult(bool);
    void updateQuizTimer(int timeRemaining);

signals:
    void enterReferenceMode();
    void submitCocktail(Cocktail*);
    void learnSignal();
    void quizSignal();
    void quizEnding();

private:
    Ui::MainWindow *ui;
    Model *model;
    QFont defaultChalkboardFont;
    int barBottleCount;
    int barMixerCount;
    int barGarnishCount;
    int barGlassCount;

    enum mode {
        home,
        learn,
        quiz
    };

    int chalkboardDelay = 50;

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

    //Stores default location, size and iconSize for bottles, garnish, etc.
    QMap<QAbstractButton *, buttonData> defaultButtonData;

    QMap<QString, double> ingredientVolumes;       //Volumes of spirits and mixers
    QMap<QString, QStringList> garnishOptions;     //Available options for various garnishes
    QStringList iceOptions;                        //Options for ice

    QSet<QString> garnishSelection;                //Currently selected Garnish
    QString iceSelection;                          //Currently selected ice option
    QString glassSelection;                        //currently seledted glassware

    QPropertyAnimation *buttonTranslation;
    QPropertyAnimation *buttonScale;
    QPropertyAnimation *buttonIconScale;

    InfoDialog* info;

    Cocktail currentCocktail;

    void moveButtonToShelf(QAbstractButton * button, QButtonGroup &group, int &count);
    void moveButtonToBar(QAbstractButton * button, QButtonGroup &shelfGroup, QButtonGroup &barGroup, int &count, QVector<QLabel*> &barPositions);
    void clearBar();

    void findButton(QString text);
    void writeMessage(QString message);
    void delay( int millisecondsToWait );
    void disableButtons();
    void enableButtons();
    void fancyDisable(QAbstractButton * button);
};
#endif // MAINWINDOW_H
