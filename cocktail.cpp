#include "cocktail.h"
#include <QStringList>

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

bool Cocktail::operator==(Cocktail other) {
    bool glassesMatch = (this->getGlass() == other.getGlass());
    bool icesMatch = (this->getIce() == other.getIce());
    bool ingredientsMatch = (this->ingredients==other.ingredients);
    bool garnishesMatch = (this->garnishes == other.garnishes);

//    // iterate through all of this recipe's garnishes,
//    // see if other has an equivalent garnish or substitute
//    garnishesMatch = true;
//    for(garnish g : this->garnishes){

//        // true if other has the garnish needed
//        bool otherHasMatch = other.garnishes.contains(g);
//        // true if other has a substitute for the garnish needed
//        bool otherHasSubstitute = (this->garnishSubstitutions[g].intersects(other.garnishes));

//        if(!otherHasMatch && !otherHasSubstitute){
//            garnishesMatch = false;
//            break;
//        }
//    }

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

