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
 *  Style Checked by : Grayson Spencer - u1103228
 **/

#include <QTimer>
#include <QFile>
#include <QTextStream>
#include "model.h"
#include "cocktail.h"

Model::Model(QObject *parent) : QObject(parent), allCocktails(getAllCocktailsFromCsv()), quizTimer(this) {
    quizTimer.setInterval(1000);
    connect(&quizTimer,SIGNAL(timeout()),SLOT(updateTimer()));
}

// Reference slots
void Model::startReferenceMode() {
    emit allCocktailsUpdated(allCocktails);
}

// Learning slots
void Model::sendNextCocktailLearning() {
    emit nextCocktailReadyLearning(allCocktails[chooseNextCocktailIndex()]);
}

// Quiz slots
void Model::sendNextCocktailQuiz() {
    elapsedQuizTime = 0;
    currentCocktailQuizIndex = chooseNextCocktailIndex();

    emit nextCocktailReadyQuiz( allCocktails[currentCocktailQuizIndex] );
    startTimer();
}

void Model::evaluateCocktail(Cocktail creation){
    // stop timer immediately
    stopTimer();
    emit timeUpdatedQuiz(0);

    bool success = ( isCreationFollowingRecipe(creation, allCocktails[currentCocktailQuizIndex]) );
    allCocktails[currentCocktailQuizIndex].updateStats(success, elapsedQuizTime);

    // reset the quiz time after updateStats() has been called
    elapsedQuizTime = 0;

    if(success) {
        if(checkLevelUp()) {
            userLevel++;
            emit userLeveledUp(userLevel);
        }
        else
            emit cocktailResultReadyQuiz(success);
    }
    else
        emit cocktailResultReadyQuiz(success);

    // Update the reference mode with the new stats.
    emit allCocktailsUpdated(allCocktails);
};

bool Model::checkLevelUp(){
    int totalSuccesses = 0;
    int totalFailures = 0;

    // Count total attempts at the current cocktail.
    for (auto & cocktail : allCocktails) {
        totalSuccesses += cocktail.getSuccesses();
        totalFailures += cocktail.getFailures();
    }

    // Create the new accuracy depending on the total attempts.
    double accuracy = totalSuccesses/double(totalSuccesses + totalFailures);

    //A user can be promoted to the next level, but cannot be moved back
    //level 1
    if (totalSuccesses >= 1 && accuracy > 0.5 && userLevel < 1)
        return true;
    //level 2
    else if (totalSuccesses >= 3 && accuracy > 0.6 && userLevel < 2)
        return true;
    //level 3
    else if (totalSuccesses >= 8 && accuracy > 0.75 && userLevel < 3)
        return true;
    //level 4
    else if (totalSuccesses >= 18 && accuracy > 0.9 && userLevel < 4)
        return true;
    //level 5
    else if (totalSuccesses >= 18 && accuracy == 1.0 && userLevel < 5)
        return true;
    else
        return false;
}

void Model::endQuiz(){
    stopTimer();
    elapsedQuizTime = 0;
}


/////////////////////// //
/// Helper Methods     //
///////////////////// //

int Model::chooseNextCocktailIndex(){
    int origChosenIndex = rand() % allCocktails.length();
    int chosenIndex = origChosenIndex;
    bool isRepeat;
    bool mustChooseRepeat;

    do {
        // find a new choice
        chosenIndex = (chosenIndex + 1) % allCocktails.length();
        Cocktail nextCocktail = allCocktails[chosenIndex];

        // re-check conditions
        isRepeat = recentHistoryIndices.contains(chosenIndex);

        // avoid infinite loop: if both conditions can't be satisfied, just choose anything with the right difficulty
        if(chosenIndex == origChosenIndex)
            mustChooseRepeat = true;

    } while( isRepeat );

    recentHistoryIndices.enqueue(chosenIndex);

    if(recentHistoryIndices.size() > MAX_HISTORY_LENGTH) {
        recentHistoryIndices.dequeue();
    }

    return chosenIndex;
}

bool Model::isCreationFollowingRecipe(Cocktail creation, Cocktail recipe) {
    bool glassesMatch = (recipe.getGlass() == creation.getGlass());
    bool icesMatch = (recipe.getIce() == creation.getIce());
    bool ingredientsMatch = (recipe.getIngredientsMap() == creation.getIngredientsMap());
    bool garnishesMatch;

    // iterate through all of the recipe's garnishes,
    // creation must have the garnish OR a valid substitution
    garnishesMatch = true;
    foreach (const QString& gar, recipe.getGarnishSet()) {
        bool creationHasMatch = creation.getGarnishSet().contains(gar);
        bool recipeAllowsSubstitution = (recipe.getGarnishSubstitutionsMap()[gar].intersects(creation.getGarnishSet())); // dernmine if recipe for cocktail can be replaced with another garnish

        if( !(creationHasMatch || recipeAllowsSubstitution) ) {
            garnishesMatch = false;
            break;
        }
    }
    return glassesMatch && icesMatch && ingredientsMatch && garnishesMatch;
}



//////////////////// //
/// Timer Methods   //
////////////////// //
void Model::startTimer(){
    quizTimer.start();
}

void Model::stopTimer(){
    quizTimer.stop();
}

void Model::updateTimer(){
    elapsedQuizTime += quizTimer.interval()/1000.0;
    emit timeUpdatedQuiz(elapsedQuizTime);
}


// /////////////////////// //
// COCKTAIL INIT. FUNCTION //
// /////////////////////// //

Cocktail parseCocktailData(QString drinkRecord){
    char delim = '|';
    QString name = drinkRecord.section(delim, 0, 0);
    QString difficulty = drinkRecord.section(delim, 1, 1);
    QString description = drinkRecord.section(delim, 2, 2);
    QString instructions = drinkRecord.section(delim, 3, 3);
    QString glass = drinkRecord.section(delim, 4, 4);
    QString ice = drinkRecord.section(delim, 5, 5);
    QString ingredients = drinkRecord.section(delim, 6, 6);
    QString garnish = drinkRecord.section(delim, 7, 7);
    QString cocktailImagePath = drinkRecord.section(delim, 8, 8);

    Cocktail currDrink(name, difficulty, description, instructions, glass, ice, ingredients, garnish, cocktailImagePath);

    return currDrink;
}

QVector<Cocktail> Model::getAllCocktailsFromCsv() {
    QVector<Cocktail> tempAllCocktails;
    QFile cocktailData(":/Data/CocktailData.csv");

    if (!cocktailData.open(QIODevice::ReadOnly | QIODevice::Text))
        return tempAllCocktails;

    QTextStream in(&cocktailData);

    while (!in.atEnd()){
        QString line = in.readLine();
        tempAllCocktails.append(parseCocktailData(line));
    }

    return tempAllCocktails;
}
