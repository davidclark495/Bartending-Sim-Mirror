#ifndef COCKTAILWIDGET_H
#define COCKTAILWIDGET_H
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
 *  Style Checked by : Grayson Spencer - u1103228
 **/

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

public slots:
    // applies physics + buoyancy to the ice cube
    void updateWorld();

private:
    static bool isIceInFluid;

    int scaleFactor = 20; // world scale is 1/20th of screen scale (must scale x*20 and y*20)
    b2World world;
    b2Body* floorBody; // represents the bottom of the glass
    b2Body* leftWallBody;
    b2Body* rightWallBody;
    b2Body* ceilBody; // represents the top of the glass, point where fluid must stop
    b2Body* fluidBody; // represents the rising fluid
    b2Body* iceBody;

    QTimer timer;

    QImage iceImage;
    QImage floorImage;
    QImage ceilImage;
    QImage wallImage;
    QImage fluidImage;

    // listener for particular collisions, e.g. ice + fluid
    class OverflowListener : public b2ContactListener {
    public:
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
    } *overflowListener;

    // calculate forces exerted by a fluid on a box
    static b2Vec2 calcBuoyancyForce(b2Fixture box, b2Fixture fluid);
    static b2Vec2 calcDragForce(b2Fixture box, b2Fixture fluid);

    // misc. helpers
    b2Vec2 getTopLeftPointOfRectBody(b2Body*);
};

#endif // CocktailWidget_H
