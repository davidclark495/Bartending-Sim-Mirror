#ifndef COCKTAIL_H
#define COCKTAIL_H

#include <QMap>
#include <QSet>



// Represents a cocktail.
// Holds general-knowledge descriptions & in-game instructions.
class Cocktail
{
    // public interface
public:
    Cocktail ();
    Cocktail(QString name, QString difficulty, QString desc, QString instr, QString glass, QString ice, QString ingedients, QString garnish); // recommended for official/named cocktails
    Cocktail(QString glass, QString ice, QMap<QString, double> ingredients, QSet<QString> garnish); //Cocktails created in quiz mode only need these items

    bool operator==(Cocktail); // Cocktails are equal if they contain the same glass, ice, ingredients, garnishes
    bool operator!=(Cocktail);

    QString getName();
    QString getDifficulty();
    QString getDescription();
    QString getInstructions();
    QString getGlass();
    QString getIce();
    QString getIngredients();
    QString getGarnish();
    QSet<QString> getGarnishSet();
    QMap<QString, double> getIngredientsMap();

    QMap<QString, double>::Iterator allIngredients();
    QSet<QString>::Iterator allGarnishes();

private:
    // the descriptive elements of a cocktail
    QString myName;
    QString myDifficulty;
    QString description; // flavor text, includes history
    QString instructions; // how you would make it

    // the components needed to make a given cocktail

    QString myGlass;

    QString myIce;

    // e.g. recipe calls for lemon, can be replaced w/ lime or kiwi
    // garnishSubstitutions = <lemon, [lime, kiwi]>
//    QMap<garnish, QSet<garnish>> garnishSubstitutions;

    QMap<QString, double> ingredients;
    QSet<QString> garnishes;
    QMap<QString, QSet<QString>> garnishSubstitutions;

};

#endif // COCKTAIL_H
