#include "model.h"

Model::Model(QObject *parent) : QObject(parent)
{

}

// Menu slots
void Model::input_StartReferenceActivity(){};
void Model::input_StartLearningActivity(){};
void Model::input_StartQuizActivity(){};

// Reference slots
void Model::input_NextPage(){};
void Model::input_PrevPage(){};
void Model::input_Cocktail(cocktail selected){};
void Model::input_SearchForCocktail(QString cocktailName){};

// Learning slots
// input_Cocktail can be used here

// Quiz slots
void Model::input_Glass(glass selected){};
void Model::input_Drink(drink selected, double amount){};
void Model::input_Ice(ice selected, double amount){};
void Model::input_Ingredient(ingredient selected, double amount){};
void Model::input_Garnish(garnish selected, double amount){};
void Model::input_EndInput(){}; // called when user has finished adding components (e.g. adding drinks/ingredients)
void Model::input_Restart(){}; // trash the current drink, go back to glass selection
