#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class Model : public QObject
{
    Q_OBJECT

// get rid of this eventually
private:
    // enums in separate file
    enum FinishedDrink {};
    enum Glass {};
    enum Drink {};
    enum Ingredient {};
    enum Garnish {};

public:
    explicit Model(QObject *parent = nullptr);

public slots:
    // Menu slots
    void startReferenceActivity();
    void startLearningActivity();
    void startQuizActivity();

    // Reference slots
    void input_SearchDrinks(QString drinkName);

    // Learning slots
    void input_FinishedDrink(FinishedDrink selected); // return a vector<DrinkComponent>, show the recipe

    // Quiz slots
    void input_Glass(Glass);
    void input_Drink(Drink);
    void input_Ingredient(Ingredient);
    void input_Garnish(Garnish);
    void input_EndInput(); // called when user has finished adding components (e.g. adding drinks/ingredients)

signals:
    // Menu signals
    // Reference signals
    // Learning signals
    // Quiz signals
    void toNextStep_Glasses();
    void toNextStep_Drinks();
    void toNextStep_Ingredients();
    void toNextStep_Garnishes();

    void output_SuccessfulDrink(FinishedDrink drinkMade);
    void output_FailedDrink();

private:
    enum GameMode { start, reference, learning, quiz };
    struct drinkRecord {
        double accuracy;
        double speed;
        int numMade;
    };
    struct playerRecord{
        int maxStreak;
    };
    struct recipe{
        Glass glass;
        QVector<Drink> componentDrinks;
        QVector<Ingredient> ingredients;
        QVector<Garnish> garnishes;
    };
    struct drink {
        FinishedDrink name;
        recipe recipe;
        QString description;
    };

    // reference
    const QVector<drink> allDrinks;

    // state
    GameMode currentMode;
    std::map<FinishedDrink, drinkRecord> allDrinkRecords;
    playerRecord playerRecords;

    // sub-Models
//    ReferenceModel* refModel;
//    LearningModel* learnModel;
//    QuizModel* quizModel;
//    //  state
//    //    recipe recipeSoFar;
//    //    int currentStreak;

//    quizModel.reset();
//    quizModel.start();
};

#endif // MODEL_H
