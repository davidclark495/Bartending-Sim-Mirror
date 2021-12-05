#include "model.h"
#include "cocktail.h"

Model::Model(QObject *parent) : QObject(parent), allCocktails(getAllCocktailsMap()) {
  currentMode=start;
}

// Menu slots
void Model::startReferenceMode(){
     currentMode=reference;
     emit display_CocktailMap(allCocktails);
}
void Model::startLearningMode(){
    currentMode=learning;
}
void Model::startQuizMode(){
    currentMode=quiz;
    int numCocktails = allCocktails.values().length();
    int randIndex = rand() % numCocktails;
    currentQuiz = allCocktails.values().at(randIndex); // the next cocktail
    emit output_NextOrder(currentQuiz);
}

// Reference slots

// Learning slots
void Model::nextCocktail(){// randomly chooses the next cocktail to learn
    int randIndex = rand() % allCocktails.values().length();
    Cocktail next = allCocktails.values().at(randIndex);
    emit display_Cocktail(next);
}


// Quiz slots
void Model::evaluate_Cocktail(Cocktail creation){
   emit output_SuccessCocktail(creation==currentQuiz);
};


// /////////////////////// //
// COCKTAIL INIT. FUNCTION //
// /////////////////////// //

// called by constructor
// gets a list of cocktails, used to initialize a const variable
QMap<Cocktail::name, Cocktail> Model::getAllCocktailsMap() {
    QMap<Cocktail::name, Cocktail> tempAllCocktails;

    // kind of a hack,
    // defining cocktails by hand in block scopes
    // might be the best short-term solution

    {// WHITE RUSSIAN
        Cocktail::name nm = Cocktail::name::whiteRussian;
        QString stringName = "White Russian";
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "The White Russian is a decadent and surprisingly easy-to-make cocktail. Combining vodka, Kahlúa and cream and serving it on the rocks creates a delicious alternative to adult milkshakes. \nIt would be a great story to say that the White Russian’s star rose from that point on, but that would not be true. The truth is the White Russian suffered a bit from a stodgy, antiquated reputation until the 1998 movie “The Big Lebowski” came along and breathed new life into the cocktail with Jeff Bridges’ character, the Dude, sipping it exclusively—and constantly. It’s one of popular culture’s best drinks-related successes.";
        QString instructions = "When making a White Russian at home, choose a decent vodka (a Russian one, if you want to stay on theme) and a good heavy cream. Half-and-half can work in a pinch, but milk will produce a thin drink. Remember: You’re aiming for decadence.";

        Cocktail whiteRussian(nm, stringName, diff, description, instructions);

        whiteRussian.setGlass( Cocktail::glass::lowball );
        whiteRussian.setIce( Cocktail::ice::rocks );

        whiteRussian.addIngredient(Cocktail::ingredient::vodka, 2.0);
        whiteRussian.addIngredient(Cocktail::ingredient::kahlua, 1.0);
        whiteRussian.addIngredient(Cocktail::ingredient::heavyCream, 1.0);

        tempAllCocktails.insert(nm, whiteRussian);
    }

    {// OLD FASHIONED
        // check: bourbon or ryeWhiskey?
        Cocktail::name nm = Cocktail::name::oldFashioned;
        QString stringName = "Old Fashioned";
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "There may be no better test of a bartender's mettle than ordering an Old Fashioned. The recipe is simple:";
        QString instructions = "Put sugar in glass. Cover it with dashes of bitters. Add whiskey and stir until sugar dissolves. Add ice, stir again, and serve. If the barman starts shaking the ingredients or muddling fruit, have your next round at another bar.";
        Cocktail oldFashioned(nm, stringName, diff, description, instructions);

        oldFashioned.setGlass( Cocktail::glass::lowball );
        oldFashioned.setIce( Cocktail::ice::rocks );

        oldFashioned.addIngredient(Cocktail::ingredient::bourbon, 2.0);
        oldFashioned.addIngredient(Cocktail::ingredient::angosturaBitters, 2.0);
        oldFashioned.addIngredient(Cocktail::ingredient::sugarCube, 1.0);

        oldFashioned.addGarnish(Cocktail::garnish::orangeTwist);

        tempAllCocktails.insert(nm, oldFashioned);
    }

    {// MARGARITA
        Cocktail::name nm = Cocktail::name::margarita;
        QString stringName = "Margarita";
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "Cloyingly sweet margarita mixes have given this drink a bad name. A well-made version is a fresh mix of lime juice and tequila, with a hint of sweetener.";
        QString instructions = "";
        Cocktail margarita(nm, stringName, diff, description, instructions);

        margarita.setGlass( Cocktail::glass::cocktail );
        margarita.setIce( Cocktail::ice::straightUp );

        margarita.addIngredient(Cocktail::ingredient::silverTequila, 2.0);
        margarita.addIngredient(Cocktail::ingredient::cointreau, 1.0);
        margarita.addIngredient(Cocktail::ingredient::limeJuice, 1.0);

        margarita.addGarnish(Cocktail::garnish::limeWedge);

        tempAllCocktails.insert(nm, margarita);
    }

    {// COSMOPOLITAN
        Cocktail::name nm = Cocktail::name::cosmopolitan;
        QString stringName = "Cosmoplitan";
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "The cosmo became almost ubiquitous in the '90s thanks to the TV show Sex and the City, but this spin on the martini remains just as tasty today as when Carrie Bradshaw made it famous.";
        QString instructions = "Build all ingredients in a shaker tine with ice and shake. Strain into a martini glass and garnish with lime wheel or zest.";
        Cocktail cosmopolitan(nm, stringName, diff, description, instructions);

        cosmopolitan.setGlass( Cocktail::glass::cocktail );
        cosmopolitan.setIce( Cocktail::ice::straightUp );

        cosmopolitan.addIngredient(Cocktail::ingredient::citrusVodka, 1.5);
        cosmopolitan.addIngredient(Cocktail::ingredient::cointreau, 1.0);
        cosmopolitan.addIngredient(Cocktail::ingredient::limeJuice, 0.5);
        cosmopolitan.addIngredient(Cocktail::ingredient::cranberryJuice, 0.25);

        cosmopolitan.addGarnish(Cocktail::garnish::lemonSlice);

        tempAllCocktails.insert(nm, cosmopolitan);
    }

    {// NEGRONI
        Cocktail::name nm = Cocktail::name::negroni;
        QString stringName = "Negroni";
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "A favorite of bartenders all over the world, the Negroni is a simple three-ingredient cocktail.";
        QString instructions = "Stir ingredients with ice.";
        Cocktail negroni(nm, stringName, diff, description, instructions);

        negroni.setGlass( Cocktail::glass::lowball );
        negroni.setIce( Cocktail::ice::rocks );

        negroni.addIngredient(Cocktail::ingredient::gin, 1.0);
        negroni.addIngredient(Cocktail::ingredient::campari, 1.0);
        negroni.addIngredient(Cocktail::ingredient::sweetVermouth, 1.0);

        negroni.addGarnish(Cocktail::garnish::orangeTwist);

        tempAllCocktails.insert(nm, negroni);
    }

    {// MOSCOW MULE
        Cocktail::name nm = Cocktail::name::moscowMule;
        QString stringName = "Moscow Mule";
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "Popular for good reason, the Moscow Mule is one of the most refreshing things to sip on a hot summer day. Its suggested vessel, a copper mug, also just looks sharp.";
        QString instructions = "Squeeze lime juice into a Moscow Mule mug. Add two or three ice cubes, pour in the vodka, and fill with cold ginger beer. Stir and serve.";
        Cocktail moscowMule(nm, stringName, diff, description, instructions);

        moscowMule.setGlass( Cocktail::glass::copperCup );
        moscowMule.setIce( Cocktail::ice::rocks );

        moscowMule.addIngredient(Cocktail::ingredient::vodka, 2.0);
        moscowMule.addIngredient(Cocktail::ingredient::gingerBeer, 4.0);
        moscowMule.addIngredient(Cocktail::ingredient::limeJuice, 0.5);

        moscowMule.addGarnish(Cocktail::garnish::limeSlice);

        tempAllCocktails.insert(nm, moscowMule);
    }

    {// MARTINI
        // check: ice? gin or vodka?
        Cocktail::name nm = Cocktail::name::martini;
        QString stringName = "Martini";
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "";
        QString instructions = "";
        Cocktail martini(nm, stringName, diff, description, instructions);

        martini.setGlass( Cocktail::glass::cocktail );
        martini.setIce( Cocktail::ice::rocks );

        martini.addIngredient(Cocktail::ingredient::gin, 3.0);
        martini.addIngredient(Cocktail::ingredient::dryVermouth, 0.5);

        martini.addGarnish(Cocktail::garnish::lemonTwist);
        martini.allowSubstitution(Cocktail::garnish::lemonTwist, Cocktail::garnish::olive);

        tempAllCocktails.insert(nm, martini);
    }

    {// MIMOSA
        Cocktail::name nm = Cocktail::name::mimosa;
        QString stringName = "Mimosa";
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "We'd like to salute Frank Meier, the bartender at the Ritz Paris who in 1925 reportedly served the first mimosa. The recipe just might be the simplest cocktail ever created.";
        QString instructions = "";
        Cocktail mimosa(nm, stringName, diff, description, instructions);

        mimosa.setGlass( Cocktail::glass::champagneFlute );
        mimosa.setIce( Cocktail::ice::neat );

        mimosa.addIngredient(Cocktail::ingredient::champagne, 2.5);
        mimosa.addIngredient(Cocktail::ingredient::orangeJuice, 2.5);

        mimosa.addGarnish(Cocktail::garnish::strawberry);

        tempAllCocktails.insert(nm, mimosa);
    }

    {// TEMPLATE
        Cocktail::name nm = Cocktail::name::moscowMule;
        QString stringName = "Moscow Mule";
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "";
        QString instructions = "";
        Cocktail moscowMule(nm, stringName, diff, description, instructions);

        moscowMule.setGlass( Cocktail::glass::copperCup );
        moscowMule.setIce( Cocktail::ice::rocks );

        moscowMule.addIngredient(Cocktail::ingredient::vodka, 2.0);
        moscowMule.addIngredient(Cocktail::ingredient::gingerBeer, 4.0);
        moscowMule.addIngredient(Cocktail::ingredient::limeJuice, 0.5);

        moscowMule.addGarnish(Cocktail::garnish::limeSlice);

        tempAllCocktails.insert(nm, moscowMule);
    }


    {// MANHATTAN
        // check: ice? garnish?
        Cocktail::name nm = Cocktail::name::manhattan;
        QString stringName = "Manhattan";
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "Created sometime in the mid-1800s, the Manhattan is one of the booziest classic drink recipes.";
        QString instructions = "Stir ingredients in a mixing glass with ice. Strain into chilled martini glass or cocktail coupe.";

        Cocktail manhattan(nm, stringName, diff, description, instructions);

        manhattan.setGlass( Cocktail::glass::cocktail );
        manhattan.setIce( Cocktail::ice::rocks );

        manhattan.addIngredient(Cocktail::ingredient::ryeWhiskey, 2.0);
        manhattan.addIngredient(Cocktail::ingredient::sweetVermouth, 1.0);
        manhattan.addIngredient(Cocktail::ingredient::angosturaBitters, 2.0);

        manhattan.addGarnish(Cocktail::garnish::maraschinoCherry);
        manhattan.allowSubstitution(Cocktail::garnish::maraschinoCherry, Cocktail::garnish::orangeTwist);

        tempAllCocktails.insert(nm, manhattan);
    }

    return tempAllCocktails;
    // alternative to hard-coding: write this method --> readSpreadsheet(file);
}
