#include "cocktail.h"
#include <QStringList>


Cocktail::Cocktail() { }

//Cocktail::Cocktail(name nm, difficulty diff, QString description, QString instructions) {
//    this->myName = nm;
//    this->myDifficulty = diff;
//    this->description = description;
//    this->instructions = instructions;
//}

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


// ///////// //
// Accessors //
// ///////// //

//enum Cocktail::name Cocktail::getName() {
//    return myName;
//}

//enum Cocktail::difficulty Cocktail::getDifficulty() {
//    return myDifficulty;
//}


//enum Cocktail::glass Cocktail::getGlass() {
//    return myGlass;
//}

//enum Cocktail::ice Cocktail::getIce() {
//    return myIce;
//}

//QMap<Cocktail::ingredient, double>::Iterator Cocktail::allIngredients() {
//    return ingredients.begin();
//}

//QSet<Cocktail::garnish>::Iterator Cocktail::allGarnishes() {
//    return garnishes.begin();
//}


// ///////////////////////////////// //
// Accessors - Convenience Functions //
// ///////////////////////////////// //

QString Cocktail::getDescription() {
    return description;
}

QString Cocktail::getInstructions() {
    return instructions;
}

QString Cocktail::getName(){
    return myName;
}

// Same as enumToString(getDifficulty())
QString Cocktail::getDifficulty(){
    return myDifficulty;
}

// Same as enumToString(getGlass())
QString Cocktail::getGlass(){
    return myGlass;
}

// Same as enumToString(getIce())
QString Cocktail::getIce(){
    return myIce;
}


// //////// //
// Mutators //
// //////// //

//void Cocktail::setGlass(glass newGlass) {
//    myGlass = newGlass;
//}
//void Cocktail::setIce(ice newIce) {
//    myIce = newIce;
//}

// adds to the list of ingredients by
// increasing the amount of the given ingredient
//void Cocktail::addIngredient(ingredient newIngredient, double amount){
//    ingredients[newIngredient] += amount;
//}

// adds the garnish to the set of garnishes
// (adding the same garnish twice won't change anything)
//void Cocktail::addGarnish(garnish newGarnish){
//    garnishes.insert(newGarnish);
//}

//void Cocktail::allowSubstitution(garnish expected, garnish substitute){
//    garnishSubstitutions[expected].insert(substitute);
//}


// //////////// //
// Enum helpers //
// //////////// //

//QString Cocktail::enumToString(name nm) {
//    QString result;
//    switch(nm) {
//    case whiteRussian:
//        result = "White Russian";
//        break;
//    case oldFashioned:
//        result = "Old Fashioned";
//        break;
//    case margarita:
//        result = "Margarita";
//        break;
//    case cosmopolitan:
//        result = "Cosmopolitan";
//        break;
//    case negroni:
//        result = "Negroni";
//        break;
//    case moscowMule:
//        result = "Moscow Mule";
//        break;
//    case kentuckyMule:
//        result = "Kentucky Mule";
//        break;
//    case martini:
//        result = "Martini";
//        break;
//    case mojito:
//        result = "Mojito";
//        break;
//    case whiskeySour:
//        result = "Whiskey Sour";
//        break;
//    case manhattan:
//        result = "Manhattan";
//        break;
//    case gimlet:
//        result = "Mimosa";
//        break;
//    case mimosa:
//        result = "Mimosa";
//        break;
//    case paloma:
//        result = "Paloma";
//        break;
//    case sidecar:
//        result = "Sidecar";
//        break;
//    case mintJulep:
//        result = "Mint Julep";
//        break;
//    case daiquiri:
//        result = "Daiquiri";
//        break;
//    case screwdriver:
//        result = "Screwdriver";
//        break;
//    default:
//        result = "Name not specified.";
//    }
//    return result;
//}

//QString Cocktail::enumToString(difficulty diff) {
//    QString result;
//    switch(diff) {
//    case easy:
//        result = "Easy";
//        break;
//    case medium:
//        result = "Medium";
//        break;
//    case hard:
//        result = "Hard";
//        break;
//    default:
//        result = "Difficulty not specified.";
//    }
//    return result;
//}

//QString Cocktail::enumToString(glass g) {
//    QString result;
//    switch(g) {
//    case lowball:
//        result = "Lowball";
//        break;
//    case highball:
//        result = "Highball";
//        break;
//    case cocktail:
//        result = "Cocktail";
//        break;
//    case champagneFlute:
//        result = "Champagne Flute";
//        break;
//    case copperCup:
//        result = "Copper Cup";
//        break;
//    default:
//        result = "Glass not specified";
//        break;
//    }
//    return result;
//}

//QString Cocktail::enumToString(ice i) {
//    QString result;
//    switch(i) {
//    case neat:
//        result = "Neat";
//        break;
//    case straightUp:
//        result = "Straight Up";
//        break;
//    case rocks:
//        result = "Rocks";
//        break;
//    default:
//        result = "Ice not specified";
//    }
//    return result;
//}
