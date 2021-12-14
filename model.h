#ifndef MODEL_H
#define MODEL_H

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
    void startLearningMode();
    void nextCocktailLearning();

    // Quiz slots
    void startQuizMode();
    void nextCocktailQuiz();
    void evaluateCocktail(Cocktail *creation);
    void endQuiz();

signals:
    // Reference signals
    void sendAllCocktailsReference(QVector<Cocktail> list);

    // Learning signals
    void sendNextCocktailLearning(Cocktail);

    // Quiz signals
    void sendNextCocktailQuiz(Cocktail); // display the next Cocktail that needs to be made
    void sendTimeQuiz(double timeElapsed);
    void sendQuizResult(bool success);

private:
    QVector<Cocktail> allCocktails; // for reference + for tracking scores
    QQueue<int> recentHistoryIndices; // recently seen cocktails, avoid repeats
    const int MAX_HISTORY_LENGTH = 5;
    int currentCocktailQuizIndex;
    int currentCocktailDifficulty = 1;

    int chooseNextCocktailIndex();
    bool isCreationFollowingRecipe(Cocktail creation, Cocktail recipe);
    void goToNextDifficulty();

    // timer loop
    QTimer quizTimer;
    double elapsedQuizTime;
    void startTimer();
    void stopTimer();

    // helper methods
    QVector<Cocktail> getAllCocktails();

    //DEBUG
    void runTests();

private slots:
    //Quiz slots
    void updateTimer();



};

#endif // MODEL_H
