#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QTimer>
#include <QQueue>
#include "cocktail.h"

class Model : public QObject
{
    Q_OBJECT

private:

    // important internal structs/enums
private:
    enum gameMode { start, reference, learning, quiz };

    struct cocktailRecord { // used to track a player's history making a certain particular cocktail
        double avgAccuracy;
        double avgSpeed;
        int numMade;
    };
    struct playerRecord{ // used to track a player's history / achievements, not specific to a given cocktail
        int maxStreak;
    };


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
    void sendTimeQuiz(int timeRemaining);
    void sendCocktailResult(bool success);

private:
    // reference
    QVector<Cocktail> allCocktails; // must be set in constructor w/ an init. list
    // state
    QQueue<Cocktail> recentHistory;
    gameMode currentMode;
    std::map<Cocktail, cocktailRecord> allCocktailRecords;
    playerRecord playerRecords;
    QTimer *quizTimer;
    Cocktail currentCocktailQuiz;
    double elapsedQuizTime;
    // helper methods
    // timer loop
    void loadAllCocktails();
    QVector<Cocktail> getAllCocktails();
    void startTimer();
    void stopTimer();
    bool isRecentCocktail(Cocktail next);
    Cocktail& getRandomCocktail();

private slots:
    //Quiz slots
    void updateTimer();



};

#endif // MODEL_H
