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
    QQueue<Cocktail> recentHistory; // recently seen cocktails, avoid repeats
    QTimer quizTimer;
    int currentCocktailQuizIndex;
    double elapsedQuizTime;
    // helper methods
    // timer loop
    void loadAllCocktails();
    QVector<Cocktail> getAllCocktails();
    void startTimer();
    void stopTimer();
    bool isRecentCocktail(Cocktail next);
    int getRandCocktailIndex();

    //DEBUG
    void runTests();

private slots:
    //Quiz slots
    void updateTimer();



};

#endif // MODEL_H
