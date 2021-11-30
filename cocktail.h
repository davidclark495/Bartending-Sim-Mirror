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
    enum name { unnamed,
                oldFashioned, margarita, moscowMule, martini, mojito,
                whiskeySour, manhattan, gimlet, sazerac, mimosa, paloma,
                sidecar, mintJulep, daiquiri };
    enum difficulty { easy, medium, hard };
    enum glass { glassNotSet };
    enum ice { noIce };
    enum ingredient { noIngredient,
                      bourbon, ryeWhiskey, angosturaBitters, sugarCube, orangeTwist };
    enum garnish { noGarnish };


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

    // mutators
    void setGlass(glass);
    void setIce(ice);
    void addIngredient(ingredient, double amount);
    void addGarnish(garnish);

private:
    // the descriptive elements of a cocktail
    name name;
    difficulty difficulty;
    QString description; // flavor text, includes history
    QString instructions; // how you would make it

    // the components needed to make a given cocktail
    glass myGlass;
    ice myIce;
    QMap<ingredient, double> ingredients;
    QSet<garnish> garnishes;

};

#endif // COCKTAIL_H
