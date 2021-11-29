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
    Cocktail();     // recommended for user-created cocktails
    Cocktail(name); // recommended for named, ideal cocktails

    bool operator==(Cocktail); // Cocktails are equal if they contain the same glass, ice, ingredients, garnishes

    void addIngredient(ingredient, double amount);
    void addGarnish(garnish);

// public access to data members
public:
    // the descriptive elements of a cocktail
    name name;
    difficulty difficulty;
    QString description; // flavor text, includes history
    QString instructions; // how you would make it

    // the components needed to make a given cocktail
    glass glass;
    ice ice;
    QMap<ingredient, double> ingredients;
    QSet<garnish> garnishes;

};

#endif // COCKTAIL_H
