#ifndef COCKTAILWIDGET_H
#define COCKTAILWIDGET_H

#include <QWidget>
#include <box2d/box2d.h>
#include <QTimer>
#include <QSet>

class CocktailWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CocktailWidget(QWidget *parent = nullptr);
    ~CocktailWidget();
    void paintEvent(QPaintEvent *);

signals:

public slots:
    void updateWorld();

private:
    // static QSet<b2Body*> allIceInFluid; // list of all ice cubes that are currently floating in fluid
    static bool isIceInFluid; // assumes widget has only 1 ice cube

    int scaleFactor = 20; // world scale is 1/20th of screen scale (must scale x*20 and y*20)
    b2World world;
    b2Body* floorBody; // represents the bottom of the glass
    b2Body* ceilBody; // represents the top of the glass, point where fluid must stop
    b2Body* fluidBody; // represents the rising fluid
    b2Body* iceBody;


    QTimer timer;

    QImage iceImage;
    QImage floorImage;
    QImage ceilImage;
    //    QImage wallImage;
    QImage fluidImage;

    // goal of this is to stop the fluid once it reaches the ceiling
    // the fluid and the ceiling are both sensors
    class OverflowListener : public b2ContactListener{
    public:
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
    };
    OverflowListener* overflowListener;
    static b2Vec2 calcBuoyancyForce(b2Fixture box, b2Fixture fluid);


    // debug helpers
    void printPos(QString label, b2Vec2 position);
};

#endif // CocktailWidget_H
