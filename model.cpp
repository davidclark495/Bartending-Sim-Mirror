#include "model.h"
#include "cocktail.h"

Model::Model(QObject *parent) : QObject(parent), allCocktails(getAllCocktailsList()) {

}

// called by constructor
// gets a list of cocktails, used to initialize a const variable
QVector<Cocktail> Model::getAllCocktailsList() {
    QVector<Cocktail> tempAllCocktails;

    // kind of a hack,
    // defining cocktails by hand in block scopes
    // might be the best short-term solution
    {
        // example, drink recipe should be removed after testing
        Cocktail nullCocktail(Cocktail::name::unnamed);
        nullCocktail.glass = Cocktail::glass::glassNotSet;
        nullCocktail.ice = Cocktail::ice::noIce;
        nullCocktail.addIngredient(Cocktail::ingredient::noIngredient, 0.0);
        nullCocktail.addGarnish(Cocktail::garnish::noGarnish);
        tempAllCocktails.append(nullCocktail);
    }

    {
        // example, drink recipe is not accurate
        Cocktail manhattan(Cocktail::name::manhattan);
        manhattan.glass = Cocktail::glass::glassNotSet;
        manhattan.ice = Cocktail::ice::noIce;
        manhattan.addIngredient(Cocktail::ingredient::angosturaBitters, 2.0);
        manhattan.addGarnish(Cocktail::garnish::noGarnish);
        tempAllCocktails.append(manhattan);
    }

    return tempAllCocktails;
    // alternative to hard-coding: write this method --> readSpreadsheet(file);
}

// Menu slots
void Model::startReferenceMode(){}
void Model::startLearningMode(){}
void Model::startStartQuizMode(){}

// Reference slots
// Learning slots

// Quiz slots
void Model::input_Cocktail(Cocktail selected){};
