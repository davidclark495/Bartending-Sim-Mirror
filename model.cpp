#include "model.h"
#include "cocktail.h"
#include "model.h"
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QRegularExpression>
#include <iostream>
Model::Model(QObject *parent) : QObject(parent), allCocktails(getAllCocktails()) {
    currentMode=start;
    quizTimer=new QTimer(this);

    quizTimer->setInterval(100);
    connect(quizTimer,SIGNAL(timeout()),SLOT(updateTimer()));
}

// Menu slots
void Model::startReferenceMode(){
    currentMode=reference;
    emit sendAllCocktailsReference(allCocktails);
}
void Model::startLearningMode(){
    currentMode=learning;
    nextCocktailLearning();

}
void Model::startQuizMode(){
    currentMode=quiz;
    recentHistory.clear();
    int numCocktails = allCocktails.length();
    int randIndex = rand() % numCocktails;
    currentCocktailQuiz = allCocktails.at(randIndex); // the next cocktail
    recentHistory.enqueue(currentCocktailQuiz);
    emit sendNextCocktailQuiz(currentCocktailQuiz);
    startTimer();
}

// Reference slots
bool Model::isRecentCocktail(Cocktail next){
    return recentHistory.contains(next);
}

Cocktail& Model::getRandomCocktail()
{
    int randIndex = rand() % allCocktails.length();
    Cocktail& nextCocktail =  allCocktails[randIndex];
    while(isRecentCocktail(nextCocktail)){
        nextCocktail= allCocktails.at(rand() % allCocktails.length());
    }
    recentHistory.append(nextCocktail);
    if(recentHistory.size()>5){
        recentHistory.dequeue();
    }
    return nextCocktail;
}
// Learning slots
void Model::nextCocktailLearning(){// randomly chooses the next cocktail to learn
    emit sendNextCocktailLearning(getRandomCocktail());
}

void Model::nextCocktailQuiz(){
    elapsedQuizTime=0;

    currentCocktailQuiz=getRandomCocktail();
    emit sendNextCocktailQuiz(currentCocktailQuiz);
    startTimer();
}

// Quiz slots
void Model::evaluateCocktail(Cocktail *creation){
    stopTimer();
    bool success = (*creation == currentCocktailQuiz);
    currentCocktailQuiz.updateStats(success, elapsedQuizTime);
    emit sendCocktailResult(success);
};

void Model::startTimer(){
    quizTimer->start();
}
void Model::stopTimer(){
    quizTimer->stop();
}
void Model::updateTimer(){
    elapsedQuizTime += quizTimer->interval()/1000.0;
    emit sendTimeQuiz(elapsedQuizTime);
}
void Model::endQuiz(){
    stopTimer();
    elapsedQuizTime=0;
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
