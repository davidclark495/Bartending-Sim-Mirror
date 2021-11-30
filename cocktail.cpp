#include "cocktail.h"


Cocktail::Cocktail() { }

Cocktail::Cocktail(enum name name) {
    this->name = name;
}

bool Cocktail::operator==(Cocktail other) {
    bool glassesMatch = (this->glass == other.glass);
    bool icesMatch = (this->ice == other.ice);
    bool ingredientsMatch = (this->ingredients==other.ingredients);
    bool garnishesMatch = (this->garnishes == other.garnishes);

    return glassesMatch && icesMatch && ingredientsMatch && garnishesMatch;
}

// adds to the list of ingredients by
// increasing the amount of the given ingredient
void Cocktail::addIngredient(ingredient newIngredient, double amount){
    ingredients[newIngredient] += amount;
}

void Cocktail::addGarnish(garnish newGarnish){
    garnishes.insert(newGarnish);
}

