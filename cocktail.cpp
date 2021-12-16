/**
 *
 * A9 - Bartending Simulator
 *
 *  Author:  David McLean - u0145629
 *  Author:  Grayson Spencer - u1103228.
 *  Author:  David Clark - u1225394
 *  Author:  Zachary Atherton - u1023217
 *  Class:   C3505 Fall 2021
 *  Date:   12/16/2021
 *
 *  Style Checked by :
 **/
#include <QStringList>
#include "cocktail.h"

Cocktail::Cocktail(){

}

// Create a full cocktail (with description + recipe components)
// by parsing spreadsheet-style entries.
Cocktail::Cocktail(QString name, QString difficulty, QString desc, QString instr,
                   QString glass, QString ice, QString ingredients, QString garnish, QString cocktailImage)
{
    this->name = name;
    this->difficulty = difficulty;
    this->description = desc;
    this->instructions = instr;
    this->glass = glass;
    this->ice = ice;
    this->referenceImagePath = cocktailImage;

    QStringList ingredientsList = ingredients.split("/");
    for ( const auto& ingredient : ingredientsList) {
        QString ingredientName = ingredient.section('-', 0, 0);
        QString ingredientAmount = ingredient.section('-', 1, 1);

        this->ingredients[ingredientName] = ingredientAmount.toDouble();
    }

    QStringList garnishClauseList = garnish.split("AND");
    for ( const QString& garnishClause : garnishClauseList) {
        // garnishes.insert(garnishClause.trimmed());
        QStringList garnishList = garnishClause.split("OR");

        // Save the first garnish in the clause as the default/suggested garnish,
        // allow remaining garnishes as substitutions.
        QString suggestedGarnish = garnishList.front();
        garnishList.pop_front();

        garnishes.insert(suggestedGarnish.trimmed());

        for(const QString& garnishSubstitute : garnishList) {
            allowSubstitution(suggestedGarnish.trimmed(), garnishSubstitute.trimmed());
        }
    }
}

// Create a simple cocktail with only the recipe components.
Cocktail::Cocktail(QString glass, QString ice, QMap<QString, double> ingredients, QSet<QString> garnish) {
    name = "";
    difficulty = "";
    description = "";
    instructions = "";

    this->glass = glass;
    this->ice = ice;
    this->ingredients = ingredients;
    this->garnishes = garnish;
}

bool Cocktail::operator==(const Cocktail& other) const {
    if (this == &other)
        return true;
    bool sameDescriptiveComponents = this->name == other.name
            && this->difficulty == other.difficulty
            && this->description == other.description
            && this->instructions == other.instructions;
    bool sameRecipeComponents = this->glass == other.glass
            && this->ice == other.ice
            && this->ingredients == other.ingredients
            && this->garnishes == other.garnishes
            && this->garnishSubstitutions == other.garnishSubstitutions;
    bool sameStats = this->avgTime == other.avgTime
            && this->numSuccesses == other.numSuccesses
            && this->numFailures == other.numFailures;

    return sameDescriptiveComponents && sameRecipeComponents && sameStats;
}

bool Cocktail::operator!=(const Cocktail& other) const {
    return !(*this == other);
}

// ////////// //
// Accessors  //
// ////////// //

QString Cocktail::getDescription()const {
    return description;
}

QString Cocktail::getInstructions() const{
    return instructions;
}

QString Cocktail::getName()const{
    return name;
}

QString Cocktail::getDifficulty()const{
    return difficulty;
}

QString Cocktail::getGlass()const{
    return glass;
}

QString Cocktail::getIce()const{
    return ice;
}

QMap<QString, double> Cocktail::getIngredientsMap()const
{
    return ingredients;
}

QSet<QString> Cocktail::getGarnishSet ()const
{
    return garnishes;
}

QMap<QString, QSet<QString>> Cocktail::getGarnishSubstitutionsMap()const {
    return garnishSubstitutions;
}

QString Cocktail::getReferenceImage()const
{
    return referenceImagePath;
}

// A convenience function.
// Returns a QString with the contents of getIngredientMap() readable form.
//
// ex.
// Bourbon: 2.0
// Lime Juice: 1.0
QString Cocktail::getIngredientString()const
{
    QString returnValue = "";
    foreach (const auto &key, ingredients.keys())
    {
        returnValue.append(key + ": " + QString::number(ingredients[key]));
        returnValue.append("\n");
    }

    return returnValue;
}


// A convenience function.
// Returns a QString with the contents of getGarnishSet() in a readable form.
//
// ex.
// Lime Wedge
// ex.
// Olive OR Lemon Twist
QString Cocktail::getGarnishString()const
{
    QString returnValue = "";
    foreach (const auto &garnish, garnishes)
    {
        // add the garnish
        returnValue.append(garnish);

        // add substitutions (if any)
        if(garnishSubstitutions.contains(garnish)) {
            foreach (const QString& sub, garnishSubstitutions[garnish]) {
                returnValue.append(" OR " + sub);
            }
        }

        returnValue.append("\n");
    }

    return returnValue;
}

void Cocktail::updateStats(bool success, double elapsedTime){
    double prevTotalTime = avgTime*(numSuccesses+numFailures);
    double newTotalTime = elapsedTime+prevTotalTime;

    if(success)
        numSuccesses++;
    else
        numFailures++;

    avgTime = newTotalTime/(numSuccesses+numFailures);
}

int Cocktail::getSuccesses()
{
    return numSuccesses;
}

int Cocktail::getFailures()
{
    return numFailures;

}

double Cocktail::getAvgTime()
{
    return avgTime;
}

// Return a map with <label, value> entries, both represented with QStrings.
QMap<QString, QString> Cocktail::getStats() const
{
    QMap<QString, QString> stats;
    stats["Average Time: "] = QString::number(avgTime)+" seconds";
    stats["# of Times Successfully Made: "] = QString::number(numSuccesses);
    stats["# of Times Failed: "] = QString::number(numFailures);

    int totalAttempts = numSuccesses + numFailures;
    if(totalAttempts > 0) {
        double percentAccuracy = ((double)numSuccesses)/(totalAttempts)*100;
        stats["Accuracy: "] = (QString("%1%").arg(percentAccuracy, 0, 'f', 0));
    } else {
        stats["Accuracy: "] = "N/A";
    }
    return stats;
}


// Private Helper:
// allow two garnishes to be used interchangeably
void Cocktail::allowSubstitution(QString garnish1, QString garnish2) {
    garnishSubstitutions[garnish1].insert(garnish2);
    garnishSubstitutions[garnish2].insert(garnish1);
}

