#include "model.h"
#include "cocktail.h"
#include "model.h"
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QRegularExpression>
Model::Model(QObject *parent) : QObject(parent), allCocktails(getAllCocktails()) {
    currentMode=start;
    quizTimer=new QTimer(this);

    quizTimer->setInterval(100);
    connect(quizTimer,SIGNAL(timeout()),SLOT(updateTimer()));
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
    int numCocktails = allCocktails.length();
    int randIndex = rand() % numCocktails;
    currentQuiz = allCocktails.at(randIndex); // the next cocktail
    emit output_NextOrder(currentQuiz);
}

// Reference slots

// Learning slots
void Model::nextCocktail(){// randomly chooses the next cocktail to learn
    int randIndex = rand() % allCocktails.length();
    Cocktail next = allCocktails.at(randIndex);
    currentQuiz=next;
    emit display_Cocktail(next);
}


// Quiz slots
void Model::evaluate_Cocktail(Cocktail creation){
    emit output_SuccessCocktail(creation==currentQuiz);
};
void Model::startTimer(int sec){
    timeRemaining=sec;
    quizTimer->start();
}
void Model::startTimer(){
    quizTimer->start();
}
void Model::stopTimer(){
    quizTimer->stop();
}
void Model::updateTimer(){
    timeRemaining-=.1;
    if(timeRemaining>0)
    {
        emit output_TimeRemaining(timeRemaining);
    }
    else
    {
        emit output_timerExpired();
        quizTimer->stop();
    }
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
