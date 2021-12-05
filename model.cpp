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
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "The White Russian is a decadent and surprisingly easy-to-make cocktail. Combining vodka, Kahlúa and cream and serving it on the rocks creates a delicious alternative to adult milkshakes. \nIt would be a great story to say that the White Russian’s star rose from that point on, but that would not be true. The truth is the White Russian suffered a bit from a stodgy, antiquated reputation until the 1998 movie “The Big Lebowski” came along and breathed new life into the cocktail with Jeff Bridges’ character, the Dude, sipping it exclusively—and constantly. It’s one of popular culture’s best drinks-related successes.";
        QString instructions = "When making a White Russian at home, choose a decent vodka (a Russian one, if you want to stay on theme) and a good heavy cream. Half-and-half can work in a pinch, but milk will produce a thin drink. Remember: You’re aiming for decadence.";

        Cocktail whiteRussian(nm, diff, description, instructions);

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
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "There may be no better test of a bartender's mettle than ordering an Old Fashioned. The recipe is simple:";
        QString instructions = "Put sugar in glass. Cover it with dashes of bitters. Add whiskey and stir until sugar dissolves. Add ice, stir again, and serve. If the barman starts shaking the ingredients or muddling fruit, have your next round at another bar.";
        Cocktail oldFashioned(nm, diff, description, instructions);

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
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "Cloyingly sweet margarita mixes have given this drink a bad name. A well-made version is a fresh mix of lime juice and tequila, with a hint of sweetener.";
        QString instructions = "";
        Cocktail margarita(nm, diff, description, instructions);

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
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "The cosmo became almost ubiquitous in the '90s thanks to the TV show Sex and the City, but this spin on the martini remains just as tasty today as when Carrie Bradshaw made it famous.";
        QString instructions = "Build all ingredients in a shaker tine with ice and shake. Strain into a martini glass and garnish with lime wheel or zest.";
        Cocktail cosmopolitan(nm, diff, description, instructions);

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
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "A favorite of bartenders all over the world, the Negroni is a simple three-ingredient cocktail.";
        QString instructions = "Stir ingredients with ice.";
        Cocktail negroni(nm, diff, description, instructions);

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
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "Popular for good reason, the Moscow Mule is one of the most refreshing things to sip on a hot summer day. Its suggested vessel, a copper mug, also just looks sharp.";
        QString instructions = "Squeeze lime juice into a Moscow Mule mug. Add two or three ice cubes, pour in the vodka, and fill with cold ginger beer. Stir and serve.";
        Cocktail moscowMule(nm, diff, description, instructions);

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
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "";
        QString instructions = "";
        Cocktail martini(nm, diff, description, instructions);

        martini.setGlass( Cocktail::glass::cocktail );
        martini.setIce( Cocktail::ice::rocks );

        martini.addIngredient(Cocktail::ingredient::gin, 3.0);
        martini.addIngredient(Cocktail::ingredient::dryVermouth, 0.5);

        martini.addGarnish(Cocktail::garnish::lemonTwist);
        martini.allowSubstitution(Cocktail::garnish::lemonTwist, Cocktail::garnish::olive);

        tempAllCocktails.insert(nm, martini);
    }

    {// MOJITO
        // check: ice? lime ingredient or lime garnish?
        Cocktail::name nm = Cocktail::name::mojito;
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "Originating in Cuba, this refreshing rum-based sip is filled with mint and lime—a perfect combination for sipping by the pool or beach. If you're craving a little literary cred, the mojito was also said to be a favorite of author Ernest Hemingway.";
        QString instructions = "Muddle mint into a shaker tin, then add ice and all other ingredients. Shake to chill and strain into a highball glass with ice. Top with club soda if desired and garnish with mint.";
        Cocktail mojito(nm, diff, description, instructions);

        mojito.setGlass( Cocktail::glass::highball );
        mojito.setIce( Cocktail::ice::nullIce );

        mojito.addIngredient(Cocktail::ingredient::whiteRum, 2.0);
        mojito.addIngredient(Cocktail::ingredient::limeJuice, 0.75);
        mojito.addIngredient(Cocktail::ingredient::simpleSyrup, 0.5);


        mojito.addGarnish(Cocktail::garnish::limeWedge);
        mojito.addGarnish(Cocktail::garnish::mintSprig);
        mojito.allowSubstitution(Cocktail::garnish::lemonTwist, Cocktail::garnish::olive);

        tempAllCocktails.insert(nm, mojito);
    }

    {// WHISKEY SOUR
        // check: ice?
        Cocktail::name nm = Cocktail::name::whiskeySour;
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "Perhaps the most refreshing whiskey cocktail, this is an old reliable favorite.";
        QString instructions = "Combine ingredients in a cocktail shaker and shake (bartenders use this \"dry shake\" to incorporate the egg white). Add ice and shake again. Strain over ice in a rocks glass.";
        Cocktail whiskeySour(nm, diff, description, instructions);

        whiskeySour.setGlass( Cocktail::glass::lowball );
        whiskeySour.setIce( Cocktail::ice::nullIce );

        whiskeySour.addIngredient(Cocktail::ingredient::whiskey, 2.0);
        whiskeySour.addIngredient(Cocktail::ingredient::lemonJuice, 1.0);
        whiskeySour.addIngredient(Cocktail::ingredient::sugar, 1.0);

        whiskeySour.addGarnish(Cocktail::garnish::orangeSlice);
        whiskeySour.addGarnish(Cocktail::garnish::maraschinoCherry);

        tempAllCocktails.insert(nm, whiskeySour);
    }

    {// MANHATTAN
        // check: ice? garnish?
        Cocktail::name nm = Cocktail::name::manhattan;
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "Created sometime in the mid-1800s, the Manhattan is one of the booziest classic drink recipes.";
        QString instructions = "Stir ingredients in a mixing glass with ice. Strain into chilled martini glass or cocktail coupe.";

        Cocktail manhattan(nm, diff, description, instructions);

        manhattan.setGlass( Cocktail::glass::cocktail );
        manhattan.setIce( Cocktail::ice::rocks );

        manhattan.addIngredient(Cocktail::ingredient::ryeWhiskey, 2.0);
        manhattan.addIngredient(Cocktail::ingredient::sweetVermouth, 1.0);
        manhattan.addIngredient(Cocktail::ingredient::angosturaBitters, 2.0);

        manhattan.addGarnish(Cocktail::garnish::maraschinoCherry);
        manhattan.allowSubstitution(Cocktail::garnish::maraschinoCherry, Cocktail::garnish::orangeTwist);

        tempAllCocktails.insert(nm, manhattan);
    }

    {// GIMLET
        // check: gin or vodka?
        Cocktail::name nm = Cocktail::name::gimlet;
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "The classic recipe calls for gin, but this drink is just as tasty if you substitute vodka instead.";
        QString instructions = "Shake ingredients with ice and strain into cocktail glass";
        Cocktail gimlet(nm, diff, description, instructions);

        gimlet.setGlass( Cocktail::glass::cocktail );
        gimlet.setIce( Cocktail::ice::nullIce );

        gimlet.addIngredient(Cocktail::ingredient::gin, 2.0);
        gimlet.addIngredient(Cocktail::ingredient::simpleSyrup, 0.75);
        gimlet.addIngredient(Cocktail::ingredient::limeJuice, 0.75);

        gimlet.addGarnish(Cocktail::garnish::limeWheel);

        tempAllCocktails.insert(nm, gimlet);
    }

    {// MIMOSA
        Cocktail::name nm = Cocktail::name::mimosa;
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "We'd like to salute Frank Meier, the bartender at the Ritz Paris who in 1925 reportedly served the first mimosa. The recipe just might be the simplest cocktail ever created.";
        QString instructions = "";
        Cocktail mimosa(nm, diff, description, instructions);

        mimosa.setGlass( Cocktail::glass::champagneFlute );
        mimosa.setIce( Cocktail::ice::neat );

        mimosa.addIngredient(Cocktail::ingredient::champagne, 2.5);
        mimosa.addIngredient(Cocktail::ingredient::orangeJuice, 2.5);

        mimosa.addGarnish(Cocktail::garnish::strawberry);

        tempAllCocktails.insert(nm, mimosa);
    }

    {// PALOMA
        // check: ice? grapefruit Soda to top = amount?
        Cocktail::name nm = Cocktail::name::paloma;
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "In Mexico the paloma is just as popular as the classic margarita, and with a thirst-quenching combination of tequila, lime, and grapefruit soda it's bound to become a summer favorite of yours too.";
        QString instructions = "Combine equal parts of the ingredients in a champagne flute.";
        Cocktail paloma(nm, diff, description, instructions);

        paloma.setGlass( Cocktail::glass::highball );
        paloma.setIce( Cocktail::ice::nullIce );

        paloma.addIngredient(Cocktail::ingredient::tequila, 2.0);
        paloma.addIngredient(Cocktail::ingredient::limeJuice, 0.5);
        paloma.addIngredient(Cocktail::ingredient::grapefruitSoda, 1.0);

        paloma.addGarnish(Cocktail::garnish::limeWedge);

        tempAllCocktails.insert(nm, paloma);
    }

    {// SIDECAR
        // check: ice? VS cognac?
        Cocktail::name nm = Cocktail::name::sidecar;
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "This simple mix of brandy, lemon juice, and orange liqueur dates to the 1920s. Once you try one you'll understand why the recipe has survived so long.";
        QString instructions = "Shake ingredients with ice. Strain into a rocks glass or a cocktail class with a sugar-coated rim.";
        Cocktail sidecar(nm, diff, description, instructions);

        sidecar.setGlass( Cocktail::glass::cocktail );
        sidecar.setIce( Cocktail::ice::nullIce );

        sidecar.addIngredient(Cocktail::ingredient::cognac, 2.0);
        sidecar.addIngredient(Cocktail::ingredient::cointreau, 1.0);
        sidecar.addIngredient(Cocktail::ingredient::lemonJuice, 0.75);

        sidecar.addGarnish(Cocktail::garnish::orangeTwist);

        tempAllCocktails.insert(nm, sidecar);
    }

    {// MINT JULEP
        // check: ice? difficulty? mint leaves ingredient or mint garnish?
        Cocktail::name nm = Cocktail::name::mintJulep;
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "The official drink of the Kentucky Derby is worth ordering even when you're not at Churchill Downs.";
        QString instructions = "Muddle the mint leaves and simple syrup in a mint julep cup. Add bourbon and fill with with crushed ice. Stir until the cup is frosted. Fill with more crushed ice. Serve with a straw and a mint sprig garnish.";
        Cocktail mintJulep(nm, diff, description, instructions);

        mintJulep.setGlass( Cocktail::glass::highball );
        mintJulep.setIce( Cocktail::ice::nullIce );

        mintJulep.addIngredient(Cocktail::ingredient::bourbon, 2.0);
        mintJulep.addIngredient(Cocktail::ingredient::simpleSyrup, 0.25);

        mintJulep.addGarnish(Cocktail::garnish::mintSprig);

        tempAllCocktails.insert(nm, mintJulep);
    }

    {// DAIQUIRI
        Cocktail::name nm = Cocktail::name::daiquiri;
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "Forget the sweet frozen version made with a blender. A classic daiquiri is one of the most well-balanced cocktails around.";
        QString instructions = "Shake ingredients with ice and strain into cocktail glass. Garnish with lime wheel.";
        Cocktail daiquiri(nm, diff, description, instructions);

        daiquiri.setGlass( Cocktail::glass::cocktail );
        daiquiri.setIce( Cocktail::ice::nullIce );

        daiquiri.addIngredient(Cocktail::ingredient::lightRum, 2.0);
        daiquiri.addIngredient(Cocktail::ingredient::simpleSyrup, 1.0);
        daiquiri.addIngredient(Cocktail::ingredient::limeJuice, 1.0);

        daiquiri.addGarnish(Cocktail::garnish::limeSlice);

        tempAllCocktails.insert(nm, daiquiri);
    }

    {// TEMPLATE
        Cocktail::name nm = Cocktail::name::moscowMule;
        Cocktail::difficulty diff = Cocktail::difficulty::easy;
        QString description = "";
        QString instructions = "";
        Cocktail moscowMule(nm, diff, description, instructions);

        moscowMule.setGlass( Cocktail::glass::copperCup );
        moscowMule.setIce( Cocktail::ice::rocks );

        moscowMule.addIngredient(Cocktail::ingredient::vodka, 2.0);
        moscowMule.addIngredient(Cocktail::ingredient::gingerBeer, 4.0);
        moscowMule.addIngredient(Cocktail::ingredient::limeJuice, 0.5);

        moscowMule.addGarnish(Cocktail::garnish::limeSlice);

        tempAllCocktails.insert(nm, moscowMule);
    }




    return tempAllCocktails;
    // alternative to hard-coding: write this method --> readSpreadsheet(file);
}
