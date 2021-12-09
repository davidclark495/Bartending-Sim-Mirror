#include "cocktail.h"
#include <QStringList>

Cocktail::Cocktail() {}
Cocktail::Cocktail(QString name, QString difficulty, QString desc, QString instr, QString glass, QString ice, QString ingredients, QString garnish)
{
    myName = name;
    myDifficulty = difficulty;
    description = desc;
    instructions = instr;
    myGlass = glass;
    myIce = ice;

    QStringList ingredientsList = ingredients.split("/");
    for ( const auto& ingredient : ingredientsList)
    {
        QString ingredientName = ingredient.section('-', 0, 0);
        QString ingredientAmount = ingredient.section('-', 1, 1);

        this->ingredients[ingredientName] = ingredientAmount.toDouble();
    }

    QStringList garnishList = garnish.split("/");
    for ( const auto& garnishName : garnishList)
    {
        garnishes.insert(garnishName);
    }
}

Cocktail::Cocktail(QString glass, QString ice, QMap<QString, double> ingredients, QSet<QString> garnish)
{
    myName = "";
    myDifficulty = "";
    description = "";
    instructions = "";

    myGlass = glass;
    myIce = ice;

    this->ingredients = ingredients;
    this->garnishes = garnish;
}

bool Cocktail::operator==(Cocktail other) {    
    bool glassesMatch = (this->getGlass() == other.getGlass());
    bool icesMatch = (this->getIce() == other.getIce());
    bool ingredientsMatch;
    bool garnishesMatch;
    // iterate through all of this recipe's ingredients,
    // see if other has the correct amount
    ingredientsMatch = true;
    for(QString i : this->ingredients.keys()){
        bool otherHasSameIngredient = other.ingredients.contains(i);
        bool otherHasSameAmount = (other.ingredients[i] == this->ingredients[i]);
        if( !(otherHasSameIngredient && otherHasSameAmount) ){
            ingredientsMatch = false;
            break;
        }
    }
    // iterate through all of this recipe's garnishes,
    // see if other has an equivalent garnish or substitute
    garnishesMatch = true;
    for(QString g : this->garnishes){
        bool otherHasMatch = other.garnishes.contains(g);
        bool otherHasSubstitute = (this->garnishSubstitutions[g].intersects(other.garnishes));
        if( !(otherHasMatch || otherHasSubstitute) ){
            garnishesMatch = false;
            break;
        }
    }
    return glassesMatch && icesMatch && ingredientsMatch && garnishesMatch;
}

bool Cocktail::operator!=(Cocktail other) {
    return !(*this == other);
}

// ////////// //
// Accessors  //
// ////////// //

QString Cocktail::getDescription() {
    return description;
}

QString Cocktail::getInstructions() {
    return instructions;
}

QString Cocktail::getName(){
    return myName;
}

QString Cocktail::getDifficulty(){
    return myDifficulty;
}

QString Cocktail::getGlass(){
    return myGlass;
}

QString Cocktail::getIce(){
    return myIce;
}

QString Cocktail::getIngredients()
{
    QString returnValue = "";
    foreach (const auto &key, ingredients.keys())
    {
        returnValue.append(key + ": " + QString::number(ingredients[key]));
        returnValue.append("\n");
    }

    return returnValue;
}
QMap<QString, double> Cocktail::getIngredientsMap()
{
    return ingredients;
}

QString Cocktail::getGarnish()
{
    QString returnValue = "";
    foreach (const auto &garnish, garnishes)
    {
        returnValue.append(garnish);
        returnValue.append("\n");
    }

    return returnValue;
}

QSet<QString> Cocktail::getGarnishSet ()
{
    return garnishes;
}

