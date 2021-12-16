#ifndef MODEL_H
#define MODEL_H
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
#include <QObject>
#include <QTimer>
#include <QQueue>
#include "cocktail.h"
#include <iostream>

class Model : public QObject
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = nullptr);

public slots:
    // Reference slots
    void startReferenceMode();

    // Learning slots
    void sendNextCocktailLearning();

    // Quiz slots
    void evaluateCocktail(Cocktail creation);
    void sendNextCocktailQuiz();
    void endQuiz();

signals:
    // Reference signals
    void allCocktailsUpdated(QVector<Cocktail> list);

    // Learning signals
    void nextCocktailReadyLearning(Cocktail);

    // Quiz signals
    void nextCocktailReadyQuiz(Cocktail); // display the next Cocktail that needs to be made
    void timeUpdatedQuiz(double timeElapsed);
    void cocktailResultReadyQuiz(bool success);

    // box2d
    void userLeveledUp(int level);

private:
    QVector<Cocktail> allCocktails; // for reference + for tracking scores
    QQueue<int> recentHistoryIndices; // recently seen cocktails, avoid repeats
    const int MAX_HISTORY_LENGTH = 17;
    int currentCocktailQuizIndex;
    int currentCocktailDifficulty = 1;
    int userLevel = 0;

    QVector<Cocktail> getAllCocktailsFromCsv();
    int chooseNextCocktailIndex();
    bool checkLevelUp();
    void promoteUser();
    bool isCreationFollowingRecipe(Cocktail creation, Cocktail recipe);
    void goToNextDifficulty();

    // timer loop
    QTimer quizTimer;
    double elapsedQuizTime;
    void startTimer();
    void stopTimer();

    //DEBUG
    void runTests();

private slots:
    void updateTimer();



};

#endif // MODEL_H
