#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "cocktail.h"

class Model : public QObject
{
    Q_OBJECT

// move these to the stateEnums file, eventually
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

signals:
    // display_* means display some group of buttons
    // output_* means show some non-interactive element/data

    // Menu signals
    void display_ModeSelection();

    // Reference signals
    void display_CocktailMap(QMap<Cocktail::name, Cocktail> list);

    // Learning signals
    void display_Cocktail(Cocktail);

    // Quiz signals
    void output_NextOrder(Cocktail); // display the next Cocktail that needs to be made
    void output_TimeRemaining(int timeRemaining);
    void output_SuccessCocktail(bool success);

private:
    // reference
    const QMap<Cocktail::name, Cocktail> allCocktails; // must be set in constructor w/ an init. list

    // state
    gameMode currentMode;
    std::map<Cocktail, cocktailRecord> allCocktailRecords;
    playerRecord playerRecords;
    Cocktail currentQuiz;

    // helper methods
    // timer loop
    void loadAllCocktails();
    QMap<Cocktail::name, Cocktail> getAllCocktailsMap();


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
