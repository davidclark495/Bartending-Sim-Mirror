#include "model.h"

Model::Model(QObject *parent) : QObject(parent)
{

}

// Menu slots
void Model::startReferenceActivity(){}
void Model::startLearningActivity(){}
void Model::startQuizActivity(){}

// Reference slots
void Model::input_SearchDrinks(QString drinkName){}

// Learning slots
void Model::input_FinishedDrink(FinishedDrink selected){} // return a vector<DrinkComponent>, show the recipe

// Quiz slots
void Model::input_Glass(Glass){}
void Model::input_Drink(Drink){}
void Model::input_Ingredient(Ingredient){}
void Model::input_Garnish(Garnish){}
void Model::input_EndInput(){} // called when user has finished adding components (e.g. adding drinks/ingredients)
