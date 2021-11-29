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
    void startStartQuizMode();

    // Reference slots
    // Learning slots
    // Quiz slots
    void input_Cocktail(Cocktail creation);

signals:
    // display_* means display some group of buttons
    // output_* means show some non-interactive element/data

    // Menu signals
    void display_ModeSelection();

    // Reference & Learning signals
    void display_CocktailList(QVector<Cocktail> list);

    // Quiz signals
    void output_NextOrder(Cocktail); // display the next Cocktail that needs to be made
    void output_TimeRemaining(int timeRemaining);
    void output_SuccessfulCocktail();
    void output_FailedCocktail();

private:
    // reference
    const QVector<Cocktail> allCocktails; // must be set in constructor w/ an init. list

    // state
    gameMode currentMode;
    std::map<Cocktail, cocktailRecord> allCocktailRecords;
    playerRecord playerRecords;

    // helper methods
    // timer loop
    void loadAllCocktails();
    QVector<Cocktail> getAllCocktailsList();


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
