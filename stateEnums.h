#ifndef STATEENUMS_H
#define STATEENUMS_H
#include <QObject>

enum FinishedDrinks { oldFashioned, margarita, moscowMule, martini, mojito,
                      whiskeySour, manhattan, gimlet, sazerac, mimosa, paloma,
                      sidecar, mintJulep, daiquiri};


enum Ingredients { bourbon, ryeWhiskey, angosturaBitters, sugarCube, orangeTwist };

Q_ENUMS(Ingredients)
Q_ENUMS(FinishedDrinks)
#endif // STATEENUMS_H
