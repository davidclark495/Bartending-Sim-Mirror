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

    bool operator==(const Cocktail&) const; // Cocktails are equal if they contain the same glass, ice, ingredients, garnishes
    bool operator!=(const Cocktail&) const;

    QString getName() const;
    QString getDifficulty() const;
    QString getDescription()const;
    QString getInstructions()const;
    QString getGlass()const;
    QString getIce()const;
    QString getIngredients()const;
    QString getGarnish()const;
    QSet<QString> getGarnishSet()const;
    QMap<QString, double> getIngredientsMap()const;

    void updateStats(bool success, double elapsedTime);
    QMap<QString, QString> getStats()const;
private:
    // the descriptive elements of a cocktail
    QString myName;
    QString myDifficulty;
    QString description; // flavor text, includes history
    QString instructions; // how you would make it

    // the components needed to make a given cocktail
    QString myGlass;
    QString myIce;
    QMap<QString, double> ingredients;
    QSet<QString> garnishes;

    // e.g. recipe calls for lemon, can be replaced w/ lime or kiwi
    // garnishSubstitutions = <lemon, [lime, kiwi]>
    QMap<QString, QSet<QString>> garnishSubstitutions;

    // the user-generated records & scores associated with a given cocktail
    int numSuccesses=0;
    int numFailures=0;
    double avgTime=0;


};

#endif // COCKTAIL_H
