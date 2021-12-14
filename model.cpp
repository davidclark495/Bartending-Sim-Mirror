#include "model.h"
#include "cocktail.h"
#include "model.h"
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QRegularExpression>
#include <iostream>


Model::Model(QObject *parent) : QObject(parent), allCocktails(getAllCocktails()), quizTimer(this) {

    quizTimer.setInterval(1000);
    connect(&quizTimer,SIGNAL(timeout()),SLOT(updateTimer()));
    runTests();
}

// Menu slots
void Model::startReferenceMode(){
    emit sendAllCocktailsReference(allCocktails);
}

void Model::startLearningMode(){
    nextCocktailLearning();
}

void Model::startQuizMode(){
    nextCocktailQuiz();
    startTimer();
}

// Reference slots
int Model::chooseNextCocktailIndex()
{
    int origChosenIndex = rand() % allCocktails.length();
    int chosenIndex = origChosenIndex;

    // goal: user shouldn't repeatedly see the same cocktail
    // goal: user should only be shown cocktails matching their current difficulty/skill level
    // practicality: if there aren't many cocktails in the current difficulty class,
    //                  then we may need to repeat a drink
    bool isRepeat;
    bool isWrongDifficulty;
    bool mustChooseRepeat;
    do {
        // find a new choice
        chosenIndex = (chosenIndex + 1) % allCocktails.length();
        Cocktail nextCocktail = allCocktails[chosenIndex];

        // re-check conditions
        isRepeat = recentHistoryIndices.contains(chosenIndex);
        isWrongDifficulty = (nextCocktail.getDifficulty().toInt() != currentCocktailDifficulty);

        // avoid infinite loop: if both conditions can't be satisfied, just choose anything with the right difficulty
        if(chosenIndex == origChosenIndex)
            mustChooseRepeat = true;

    } while( isWrongDifficulty || (isRepeat && !mustChooseRepeat) );

    recentHistoryIndices.enqueue(chosenIndex);
    if(recentHistoryIndices.size() > MAX_HISTORY_LENGTH){
        recentHistoryIndices.dequeue();
    }

    return chosenIndex;
}


// Learning slots
void Model::nextCocktailLearning(){// randomly chooses the next cocktail to learn
    emit sendNextCocktailLearning(allCocktails[chooseNextCocktailIndex()]);
}



// Quiz slots
void Model::nextCocktailQuiz(){
    elapsedQuizTime = 0;

    currentCocktailQuizIndex = chooseNextCocktailIndex();
    emit sendNextCocktailQuiz( allCocktails[currentCocktailQuizIndex] );
    startTimer();
}

void Model::evaluateCocktail(Cocktail *creation){
    stopTimer();

    bool success = ( isCreationFollowingRecipe(*creation, allCocktails[currentCocktailQuizIndex]) );

    allCocktails[currentCocktailQuizIndex].updateStats(success, elapsedQuizTime);
    elapsedQuizTime = 0;

    if(success)
        goToNextDifficulty();

    emit sendQuizResult(success);
    emit sendAllCocktailsReference(allCocktails);
};

// Returns true if the creation faithfully recreates the recipe.
bool Model::isCreationFollowingRecipe(Cocktail creation, Cocktail recipe) {
    bool glassesMatch = (recipe.getGlass() == creation.getGlass());
    bool icesMatch = (recipe.getIce() == creation.getIce());
    bool ingredientsMatch = (recipe.getIngredientsMap() == creation.getIngredientsMap());
    bool garnishesMatch;

    // iterate through all of the recipe's garnishes,
    // creation must have the garnish OR a valid substitution
    garnishesMatch = true;
    for(const QString& gar : recipe.getGarnishSet()){
        bool creationHasMatch = creation.getGarnishSet().contains(gar);
        bool recipeAllowsSubstitution = (recipe.getGarnishSubstitutionsMap()[gar].intersects(creation.getGarnishSet()));

        if( !(creationHasMatch || recipeAllowsSubstitution) ){
            garnishesMatch = false;
            break;
        }
    }
    return glassesMatch && icesMatch && ingredientsMatch && garnishesMatch;
}

void Model::startTimer(){
    quizTimer.start();
}

void Model::stopTimer(){
    quizTimer.stop();
}

void Model::updateTimer(){
    elapsedQuizTime += quizTimer.interval()/1000.0;
    emit sendTimeQuiz(elapsedQuizTime);
}

void Model::endQuiz(){
    stopTimer();
    elapsedQuizTime = 0;
}
// /////////////////////// //
// COCKTAIL INIT. FUNCTION //
// /////////////////////// //

Cocktail parseCocktailData(QString drinkRecord)
{
    char delim = '|';
    QString name = drinkRecord.section(delim, 0, 0);
    QString difficulty = drinkRecord.section(delim, 1, 1);
    QString description = drinkRecord.section(delim, 2, 2);
    QString instructions = drinkRecord.section(delim, 3, 3);
    QString glass = drinkRecord.section(delim, 4, 4);
    QString ice = drinkRecord.section(delim, 5, 5);
    QString ingredients = drinkRecord.section(delim, 6, 6);
    QString garnish = drinkRecord.section(delim, 7, 7);

    Cocktail currDrink(name, difficulty, description, instructions, glass, ice, ingredients, garnish);
    return currDrink;
}

// called by constructor
// gets a list of cocktails, used to initialize a const variable
QVector<Cocktail> Model::getAllCocktails() {
    QVector<Cocktail> tempAllCocktails;
    QFile cocktailData(":/Data/CocktailData.csv");

    if (!cocktailData.open(QIODevice::ReadOnly | QIODevice::Text))
        return tempAllCocktails;

    QTextStream in(&cocktailData);

    while (!in.atEnd())
    {
        QString line = in.readLine();
        tempAllCocktails.append(parseCocktailData(line));
    }

    return tempAllCocktails;
}

// keeps current difficulty within the range [1, MAX]
void Model::goToNextDifficulty() {
    currentCocktailDifficulty %= Cocktail::MAX_DIFFICULTY;
    currentCocktailDifficulty++;
}

// ///// //
// DEBUG //
// ///// //
void Model::runTests()
{
    // TEST: show that update stats works
    std::cout << "\nTEST:\tshow that cocktail stats work" << std::endl;
    {
        Cocktail cocktail = allCocktails.first();
        cocktail.updateStats(true,3);
        cocktail.updateStats(true,2);
        cocktail.updateStats(false,4);

        std::cout << cocktail.getName().toStdString() << ": " << std::endl;
        for(const QString& stat: cocktail.getStats().keys()) {
            QString statValue = cocktail.getStats()[stat];
            std::cout << stat.toStdString() << statValue.toStdString() << std::endl;
        }
    }

    // TEST: show that cocktail equality works
    std::cout << "\nTEST:\tshow that cocktail evaluation works" << std::endl;
    {
        // for each cocktail, show cocktail equals itself
        bool cocktailEqualsSelf = true;
        for(const Cocktail& cocktail : allCocktails){
            if( cocktail != cocktail ) {
                cocktailEqualsSelf = false;
            }
        }
        std::cout << "Cocktail equals itself: " << (cocktailEqualsSelf ? "True" : "False") << std::endl;


        // for each cocktail, show cocktail follows its own recipe
        bool cocktailFollowsOwnRecipe = true;
        for(const Cocktail& cocktail : allCocktails){
            if( !isCreationFollowingRecipe(cocktail, cocktail) ) {
                cocktailFollowsOwnRecipe = false;
            }
        }
        std::cout << "Cocktail follows own recipe: " << (cocktailFollowsOwnRecipe ? "True" : "False") << std::endl;

        // WARNING: this test code has bugs (race condition? iterating + modifying? idk), inconsistent
        //          underlying behaviour seems correct, will remove eventually
        // for each permitted substitution, make a cocktail and check equality
        //        bool cocktailAcceptsSubstitutions = true;
        //        for(Cocktail cocktail : allCocktails){
        //            for(QString garnish : cocktail.getGarnishSet()){
        //                if(!cocktail.getGarnishSubstitutionsMap().contains(garnish))
        //                    continue;
        //                for(QString altGarnish : cocktail.getGarnishSubstitutionsMap()[garnish]){

        //                    QSet<QString> testGarnishSet( cocktail.getGarnishSet() );
        //                    testGarnishSet.remove(garnish);
        //                    testGarnishSet.insert(altGarnish);
        //                    Cocktail copyWithSubst(cocktail.getGlass(), cocktail.getIce(),
        //                                           cocktail.getIngredientsMap(), testGarnishSet);

        //                    if(copyWithSubst != cocktail){
        //                        cocktailAcceptsSubstitutions = false;
        //                    }
        //                }
        //            }
        //        }
        //        std::cout << "Cocktail accepts substitutions: " <<
        //                     (cocktailAcceptsSubstitutions ? "True" : "False") << std::endl;
    }
}
