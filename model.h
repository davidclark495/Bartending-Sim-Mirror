#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QTimer>
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
    // Menu slots
    void startReferenceMode();
    void startLearningMode();
    void startQuizMode();

    // Reference slots

    // Learning slots
    void nextCocktail();

    // Quiz slots
    void evaluate_Cocktail(Cocktail creation);
    void startTimer(int sec);
    void startTimer();
    void stopTimer();
signals:
    // display_* means display some group of buttons
    // output_* means show some non-interactive element/data

    // Menu signals
    void display_ModeSelection();

    // Reference signals
    void display_CocktailMap(QVector<Cocktail> list);

    // Learning signals
    void display_Cocktail(Cocktail);

    // Quiz signals
    void output_NextOrder(Cocktail); // display the next Cocktail that needs to be made
    void output_TimeRemaining(int timeRemaining);
    void output_SuccessCocktail(bool success);
    void output_timerExpired();

private:
    // reference
    const QVector<Cocktail> allCocktails; // must be set in constructor w/ an init. list

    // state
    gameMode currentMode;
    std::map<Cocktail, cocktailRecord> allCocktailRecords;
    playerRecord playerRecords;
    QTimer *quizTimer;
    Cocktail currentQuiz;
    double timeRemaining;
    // helper methods
    // timer loop
    void updateTimer();
    void loadAllCocktails();
    QVector<Cocktail> getAllCocktails();


    // ///////// //
    // Ref Model //
    // ///////// //

    // sub-Models
//    QuizModel* quizModel;
//    //  state
//    //    recipe recipeSoFar;
//    //    int currentStreak;

//    quizModel.reset();
//    quizModel.start();
};

#endif // MODEL_H
