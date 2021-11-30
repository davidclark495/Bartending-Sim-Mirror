#include "model.h"
#include "cocktail.h"

Model::Model(QObject *parent) : QObject(parent), allCocktails(getAllCocktailsList()) {
  currentMode=start;
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
void Model::startReferenceMode(){
     currentMode=reference;
     emit display_CocktailList(allCocktails);
}
void Model::startLearningMode(){
    currentMode=learning;
}
void Model::startQuizMode(){
    currentMode=quiz;
    Cocktail currentQuiz=allCocktails.at(rand()%(allCocktailRecords.size()-1));
    emit output_NextOrder(currentQuiz);
}

// Reference slots
// Learning slots

// Quiz slots
void Model::evaluate_Cocktail(Cocktail creation){
   emit output_SuccessCocktail(creation==currentQuiz);
};
