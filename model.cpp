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
    {// NULL COCKTAIL
        // example, drink recipe should be removed after testing
        enum Cocktail::name name = Cocktail::name::unnamed;
        enum Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "literally nothing";
        QString instructions = "don't add anything";

        Cocktail nullCocktail(name, diff, description, instructions);

        nullCocktail.setGlass( Cocktail::glass::glassNotSet );
        nullCocktail.setIce( Cocktail::ice::noIce );
        nullCocktail.addIngredient(Cocktail::ingredient::noIngredient, 0.0);
        nullCocktail.addGarnish(Cocktail::garnish::noGarnish);

        tempAllCocktails.append(nullCocktail);
    }

    {// MANHATTAN
        // example, drink recipe is not accurate
        enum Cocktail::name name = Cocktail::name::manhattan;
        enum Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "Created sometime in the mid-1800s, the Manhattan is one of the booziest classic drink recipes.";
        QString instructions = "Stir ingredients in a mixing glass with ice. Strain into chilled martini glass or cocktail coupe.";

        Cocktail manhattan(name, diff, description, instructions);

        manhattan.setGlass( Cocktail::glass::glassNotSet );
        manhattan.setIce( Cocktail::ice::noIce );
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
