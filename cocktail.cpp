#include "cocktail.h"


Cocktail::Cocktail() { }

Cocktail::Cocktail(name nm, QString nameStr, difficulty diff, QString description, QString instructions) {
    this->myName = nm;
    this->myNameString = nameStr;
    this->myDifficulty = diff;
    this->description = description;
    this->instructions = instructions;
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

enum Cocktail::name Cocktail::getName() {
    return myName;
}

QString Cocktail::getNameString() {
    return myNameString;
}

enum Cocktail::difficulty Cocktail::getDifficulty() {
    return myDifficulty;
}

QString Cocktail::getDescription() {
    return description;
}

QString Cocktail::getInstructions() {
    return instructions;
}

enum Cocktail::glass Cocktail::getGlass() {
    return myGlass;
}

enum Cocktail::ice Cocktail::getIce() {
    return myIce;
}

QMap<Cocktail::ingredient, double>::Iterator Cocktail::allIngredients() {
    return ingredients.begin();
}

QSet<Cocktail::garnish>::Iterator Cocktail::allGarnishes() {
    return garnishes.begin();
}


// //////// //
// Mutators //
// //////// //

void Cocktail::setGlass(glass newGlass) {
    myGlass = newGlass;
}
void Cocktail::setIce(ice newIce) {
    myIce = newIce;
}

// adds to the list of ingredients by
// increasing the amount of the given ingredient
void Cocktail::addIngredient(ingredient newIngredient, double amount){
    ingredients[newIngredient] += amount;
}

// adds the garnish to the set of garnishes
// (adding the same garnish twice won't change anything)
void Cocktail::addGarnish(garnish newGarnish){
    garnishes.insert(newGarnish);
}

void Cocktail::allowSubstitution(garnish expected, garnish substitute){
    garnishSubstitutions[expected].insert(substitute);
}
