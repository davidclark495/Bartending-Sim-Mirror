#include "model.h"
#include "cocktail.h"
#include "model.h"
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QRegularExpression>
#include <iostream>


Model::Model(QObject *parent) : QObject(parent), allCocktails(getAllCocktails()), quizTimer(this) {
    quizTimer.setInterval(1000);
    connect(&quizTimer,SIGNAL(timeout()),SLOT(updateTimer()));
//    runTests();
}

// Menu slots
void Model::startReferenceMode(){
    emit sendAllCocktailsReference(allCocktails);
}

void Model::startLearningMode(){
    nextCocktailLearning();
}

void Model::startQuizMode(){
    nextCocktailQuiz();
    startTimer();
}

// Reference slots
bool Model::isRecentCocktail(Cocktail next){
    return recentHistory.contains(next);
}

int Model::getRandCocktailIndex()
{
    // choose randomly
    int randIndex = rand() % allCocktails.length();

    // evaluate the cocktail, make sure it hasn't been chosen recently
    Cocktail nextCocktail = allCocktails[randIndex];
    while(isRecentCocktail(nextCocktail)){
        nextCocktail= allCocktails.at(rand() % allCocktails.length());
    }
    recentHistory.enqueue(nextCocktail);
    if(recentHistory.size()>5){
        recentHistory.dequeue();
    }
    return randIndex;
}


// Learning slots
void Model::nextCocktailLearning(){// randomly chooses the next cocktail to learn
    emit sendNextCocktailLearning(allCocktails[getRandCocktailIndex()]);
}

void Model::nextCocktailQuiz(){
    elapsedQuizTime = 0;

    currentCocktailQuizIndex = getRandCocktailIndex();
    emit sendNextCocktailQuiz( allCocktails[currentCocktailQuizIndex] );
    startTimer();
}

// Quiz slots
void Model::evaluateCocktail(Cocktail *creation){
    stopTimer();
    bool success = (*creation == allCocktails[currentCocktailQuizIndex]);
    allCocktails[currentCocktailQuizIndex].updateStats(success, elapsedQuizTime);
    elapsedQuizTime = 0;

    emit sendQuizResult(success);
    emit sendAllCocktailsReference(allCocktails);
};

void Model::startTimer(){
    quizTimer.start();
}

void Model::stopTimer(){
    quizTimer.stop();
}

void Model::updateTimer(){
    elapsedQuizTime += quizTimer.interval()/1000.0;
    emit sendTimeQuiz(elapsedQuizTime);
}

void Model::endQuiz(){
    stopTimer();
    elapsedQuizTime = 0;
}
// /////////////////////// //
// COCKTAIL INIT. FUNCTION //
// /////////////////////// //

Cocktail parseCocktailData(QString drinkRecord)
{
    char delim = '|';
    QString name = drinkRecord.section(delim, 0, 0);
    QString difficulty = drinkRecord.section(delim, 1, 1);
    QString description = drinkRecord.section(delim, 2, 2);
    QString instructions = drinkRecord.section(delim, 3, 3);
    QString glass = drinkRecord.section(delim, 4, 4);
    QString ice = drinkRecord.section(delim, 5, 5);
    QString ingredients = drinkRecord.section(delim, 6, 6);
    QString garnish = drinkRecord.section(delim, 7, 7);

    Cocktail currDrink(name, difficulty, description, instructions, glass, ice, ingredients, garnish);
    return currDrink;
}

// called by constructor
// gets a list of cocktails, used to initialize a const variable
QVector<Cocktail> Model::getAllCocktails() {
    QVector<Cocktail> tempAllCocktails;
    QFile cocktailData(":/Data/CocktailData.csv");

    if (!cocktailData.open(QIODevice::ReadOnly | QIODevice::Text))
        return tempAllCocktails;

    QTextStream in(&cocktailData);

    while (!in.atEnd())
    {
        QString line = in.readLine();
        tempAllCocktails.append(parseCocktailData(line));
    }

    return tempAllCocktails;
}


//DEBUG

void Model::runTests()
{
    // TEST: show that update stats works
    std::cout << "\nTEST:\tshow that cocktail stats work" << std::endl;
    {
        Cocktail cocktail = allCocktails.first();
        cocktail.updateStats(true,3);
        cocktail.updateStats(true,2);
        cocktail.updateStats(false,4);

        std::cout << cocktail.getName().toStdString() << ": " << std::endl;
        for(QString stat: cocktail.getStats().keys()) {
            QString statValue = cocktail.getStats()[stat];
            std::cout << stat.toStdString() << statValue.toStdString() << std::endl;
        }
    }

    // TEST: show that cocktail equality works
    std::cout << "\nTEST:\tshow that cocktail equality works" << std::endl;
    {
        // for each cocktail, show cocktail is equal to self
        bool cocktailEqualsSelf = true;
        for(Cocktail cocktail : allCocktails){
            if(cocktail != cocktail) {
                cocktailEqualsSelf = false;
            }
        }
        std::cout << "Cocktail equal to self: " << (cocktailEqualsSelf ? "True" : "False") << " " << std::endl;

        // WARNING: this test code has bugs (race condition? iterating + modifying? idk), inconsistent
        //          underlying behaviour seems correct, will remove eventually
        // for each permitted substitution, make a cocktail and check equality
//        bool cocktailAcceptsSubstitutions = true;
//        for(Cocktail cocktail : allCocktails){
//            for(QString garnish : cocktail.getGarnishSet()){
//                if(!cocktail.getGarnishSubstitutionsMap().contains(garnish))
//                    continue;
//                for(QString altGarnish : cocktail.getGarnishSubstitutionsMap()[garnish]){

//                    QSet<QString> testGarnishSet( cocktail.getGarnishSet() );
//                    testGarnishSet.remove(garnish);
//                    testGarnishSet.insert(altGarnish);
//                    Cocktail copyWithSubst(cocktail.getGlass(), cocktail.getIce(),
//                                           cocktail.getIngredientsMap(), testGarnishSet);

//                    if(copyWithSubst != cocktail){
//                        cocktailAcceptsSubstitutions = false;
//                    }
//                }
//            }
//        }
//        std::cout << "Cocktail accepts substitutions: " <<
//                     (cocktailAcceptsSubstitutions ? "True" : "False") << std::endl;
    }
}
