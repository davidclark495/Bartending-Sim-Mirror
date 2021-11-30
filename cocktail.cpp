#include "cocktail.h"


Cocktail::Cocktail() { }

Cocktail::Cocktail(enum name name, enum difficulty difficulty, QString description, QString instructions) {
    this->name = name;
    this->difficulty = difficulty;
    this->description = description;
    this->instructions = instructions;
}

bool Cocktail::operator==(Cocktail other) {
    bool glassesMatch = (this->getGlass() == other.getGlass());
    bool icesMatch = (this->getIce() == other.getIce());
    bool ingredientsMatch = (this->ingredients==other.ingredients);
    bool garnishesMatch = (this->garnishes == other.garnishes);

    return glassesMatch && icesMatch && ingredientsMatch && garnishesMatch;
}

bool Cocktail::operator!=(Cocktail other) {
    return !(*this == other);
}



// ///////// //
// Accessors //
// ///////// //

enum Cocktail::name Cocktail::getName() {
    return name;
}

enum Cocktail::difficulty Cocktail::getDifficulty() {
    return difficulty;
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

