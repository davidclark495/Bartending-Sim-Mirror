#ifndef COCKTAIL_H
#define COCKTAIL_H
/**
 * A9 - Bartending Simulator
 *
 *  Author:  David McLean - u0145629
 *  Author:  Grayson Spencer - u1103228.
 *  Author:  David Clark - u1225394
 *  Author:  Zachary Atherton - u1023217
 *  Class:   C3505 Fall 2021
 *  Date:   12/16/2021
 *
 *  Style Checked by :
 **/
#include <QMap>
#include <QSet>

// Represents a cocktail.
// Holds general-knowledge descriptions & in-game instructions.
class Cocktail
{
    // public interface
public:
    Cocktail();
    Cocktail(QString name, QString difficulty, QString desc, QString instr,
             QString glass, QString ice, QString ingedients, QString garnish, QString cocktailImage);
    Cocktail(QString glass, QString ice, QMap<QString, double> ingredients, QSet<QString> garnish);

    bool operator==(const Cocktail&) const;
    bool operator!=(const Cocktail&) const;

    QString getName() const;
    QString getDifficulty() const;
    QString getDescription()const;
    QString getInstructions()const;
    QString getGlass()const;
    QString getIce()const;
    QMap<QString, double> getIngredientsMap()const;
    QSet<QString> getGarnishSet()const;
    QMap<QString, QSet<QString>> getGarnishSubstitutionsMap()const;
    QString getIngredientString()const;
    QString getGarnishString()const;
    QString getReferenceImage()const;

    void updateStats(bool success, double elapsedTime);
    QMap<QString, QString> getStats()const;

    int getSuccesses();
    int getFailures();
    double getAvgTime();

    static const int MAX_DIFFICULTY = 4;

private:
    // the descriptive elements of a cocktail
    QString name;
    QString difficulty; // from 1 to 4
    QString description; // flavor text, includes history
    QString instructions; // how you would make it
    QString referenceImagePath; // The path to the finished cocktail image. Used in the reference mode.

    // the components needed to make a given cocktail
    QString glass;
    QString ice;
    QMap<QString, double> ingredients;
    QSet<QString> garnishes;

    // e.g. recipe calls for lemon, can be replaced w/ lime or kiwi
    // garnishSubstitutions = <lemon, [lime, kiwi]>
    QMap<QString, QSet<QString>> garnishSubstitutions;

    // the user-generated records & scores associated with a given cocktail
    int numSuccesses = 0;
    int numFailures = 0;
    double avgTime = 0;



    // private helper methods
    void allowSubstitution(QString garnish1, QString garnish2);
};

#endif // COCKTAIL_H
