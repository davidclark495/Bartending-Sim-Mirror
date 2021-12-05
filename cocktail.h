#ifndef COCKTAIL_H
#define COCKTAIL_H

#include <QMap>
#include <QSet>



// Represents a cocktail.
// Holds general-knowledge descriptions & in-game instructions.
class Cocktail
{

    // misc. enums, meaning is particular to "Cocktail" class
public:
    enum name
    {   nullName,
        whiteRussian, oldFashioned, margarita, cosmopolitan, negroni,
        moscowMule, kentuckyMule, martini, mojito, whiskeySour, manhattan,
        gimlet, mimosa, paloma, sidecar, mintJulep, daiquiri, screwdriver
    };

    enum difficulty
    {   nullDifficulty,
        easy, medium, hard
    };

    enum glass
    {   nullGlass,
        lowball, highball, cocktail, copperCup, champagneFlute
    };

    enum ice
    {   nullIce,
        neat, rocks, straightUp
    };

    enum ingredient
    {   nullIngredient,
        vodka, kahlua, heavyCream, bourbon, ryeWhiskey, angosturaBitters, sugarCube,
        silverTequila, cointreau, limeJuice, citrusVodka, cranberryJuice, gin, campari,
        sweetVermouth, gingerBeer, dryVermouth, whiteRum, simpleSyrup, whiskey, lemonJuice,
        sugar, peychaudsBitters, absinthe, champagne, orangeJuice, tequila, grapefruitSoda,
        cognac, lightRum, brandy, armagnac, tripleSec
    };

    enum garnish
    {   nullGarnish,
        orangeTwist, orangeSlice, limeWheel, limeWedge, limeSlice, lemonSlice, lemonTwist,
        olive, maraschinoCherry, strawberry, mintSprig
    };


    // public interface
public:
    Cocktail();                                              // recommended for user-created cocktails
    Cocktail(name, difficulty, QString desc, QString instr); // recommended for official/named cocktails

    bool operator==(Cocktail); // Cocktails are equal if they contain the same glass, ice, ingredients, garnishes
    bool operator!=(Cocktail);

    // accessors
    name getName();
    difficulty getDifficulty();
    QString getDescription();
    QString getInstructions();
    glass getGlass();
    ice getIce();
    QMap<ingredient, double>::Iterator allIngredients();
    QSet<garnish>::Iterator allGarnishes();

    QString getNameText();
    QString getDifficultyText();
    QString getGlassText();
    QString getIceText();

    // mutators
    void setGlass(glass);
    void setIce(ice);
    void addIngredient(ingredient, double amount);
    void addGarnish(garnish);

    // void allowSubstitution(ingredient expected, ingredient substitute);
    void allowSubstitution(garnish expected, garnish substitute);

    // enum helpers
    static QString enumToString(name);
    static QString enumToString(difficulty);
    static QString enumToString(glass);
    static QString enumToString(ice);


private:
    // the descriptive elements of a cocktail
    name myName;
    QString myNameString;
    difficulty myDifficulty;
    QString description; // flavor text, includes history
    QString instructions; // how you would make it

    // the components needed to make a given cocktail
    glass myGlass;
    ice myIce;
    QMap<ingredient, double> ingredients;
    QSet<garnish> garnishes;

    // e.g. recipe calls for lemon, can be replaced w/ lime or kiwi
    // garnishSubstitutions = <lemon, [lime, kiwi]>
    QMap<garnish, QSet<garnish>> garnishSubstitutions;



};

#endif // COCKTAIL_H
