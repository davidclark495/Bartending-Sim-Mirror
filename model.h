#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class Model : public QObject
{
    Q_OBJECT

// move these to the stateEnums file, eventually
private:
    // enums in separate file
    enum cocktail {};
    enum glass {};
    enum drink {};
    enum ice {};
    enum ingredient {};
    enum garnish {};

// important internal structs/enums
private:
    enum gameMode { start, reference, learning, quiz };
    enum difficulty { easy, medium, hard };
    struct cocktailRecord { // used to track a player's history making a certain particular cocktail
        double avgAccuracy;
        double avgSpeed;
        int numMade;
    };
    struct playerRecord{ // used to track a player's history / achievements, not specific to a given cocktail
        int maxStreak;
    };
    struct recipe{ // tracks the components needed to make a given cocktail
        glass glass;
        QVector<drink> drinks;
        QVector<ice> ice;
        QVector<ingredient> ingredients;
        QVector<garnish> garnishes;
    };
    struct cocktailDetails { // represents a cocktail, holds a recipe and a description
        cocktail name;
        difficulty difficulty;
        recipe recipe;
        QString description;
    };

public:
    explicit Model(QObject *parent = nullptr);

public slots:
    // Menu slots
    void input_StartReferenceActivity();
    void input_StartLearningActivity();
    void input_StartQuizActivity();

    // Reference slots
    void input_NextPage();
    void input_PrevPage();
    void input_Cocktail(cocktail selected); // return a recipe, show the recipe
    void input_SearchForCocktail(QString cocktailName);

    // Learning slots
    // input_Cocktail can be used here

    // Quiz slots
    void input_Glass(glass selected);
    void input_Drink(drink selected, double amount);
    void input_Ice(ice selected, double amount);
    void input_Ingredient(ingredient selected, double amount);
    void input_Garnish(garnish selected, double amount);
    void input_EndInput(); // called when user has finished adding components (e.g. adding drinks/ingredients)
    void input_Restart(); // trash the current drink, go back to glass selection

signals:
    // display_* means display some group of buttons
    // output_* means show some non-interactive element/data

    // Menu signals
    void display_ModeSelection();//

    // Reference signals
    void display_CocktailList(QVector<cocktail> list);

    // Learning signals

    // Quiz signals
    void display_GlassSelection();
    void display_DrinkSelection();
    void display_IceSelection();
    void display_IngredientSelection();
    void display_GarnishSelection();

    void output_Time(int timeRemaining);
    void output_SuccessfulDrink(cocktail drinkMade);
    void output_FailedDrink();

private:
    // reference
    const QVector<cocktailDetails> allDrinks;

    // state
    gameMode currentMode;
    std::map<cocktail, cocktailRecord> allDrinkRecords;
    playerRecord playerRecords;

    // helper methods
    // timer loop

    // ///////// //
    // Ref Model //
    // ///////// //

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
