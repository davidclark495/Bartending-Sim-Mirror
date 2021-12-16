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
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include "cocktailwidget.h"

// init. static var's
//QSet<b2Body*> CocktailWidget::allIceInFluid = QSet<b2Body*>(); // list of all ice cubes that are currently floating in fluid
bool CocktailWidget::isIceInFluid = false;

CocktailWidget::CocktailWidget(QWidget *parent) : QWidget(parent),
    world(b2Vec2(0.0f, 10.0f)),
    timer(this)
{
    // listen for important collisions, e.g. ice + water
    overflowListener = new OverflowListener;
    world.SetContactListener(overflowListener);

    // temporarily set positions, sizes (later, used to set box2d values)
    // treated as (xCenter, yCenter, xWidth, yWidth)
    int xOffset = 4;
    int yOffset = 7;
    int randIceXOffset = rand() % 5 - 2;
    int randIceYOffset = rand() % 9 - 4;

    QRect ceilRect      = QRect(6  + xOffset, 0  + yOffset, 10, 1);
    QRect floorRect     = QRect(6  + xOffset, 22 + yOffset, 10, 20);
    QRect leftWallRect  = QRect(0  + xOffset, 5  + yOffset, 2, 20);
    QRect rightWallRect = QRect(12 + xOffset, 5  + yOffset, 2, 20);
    QRect fluidRect     = QRect(6  + xOffset, 28 + yOffset, 10, 20);
    QRect iceRect       = QRect(8  + xOffset + randIceXOffset, -10 + yOffset + randIceYOffset, 4, 4);

    // load box2d world + objects
    // FLOOR //
    {
        // Define the floor body (bottom of the glass).
        b2BodyDef floorBodyDef;
        floorBodyDef.position.Set(floorRect.x(), floorRect.y());

        // Call the body factory which allocates memory for the ground body
        // from a pool and creates the ground box shape (also from a pool).
        // The body is also added to the world.
        floorBody = world.CreateBody(&floorBodyDef);

        // Define the floor box shape.
        b2PolygonShape floorBox;
        floorBox.SetAsBox(floorRect.width()/2, floorRect.height()/2);

        // Add the ground fixture to the floor body.
        floorBody->CreateFixture(&floorBox, 0.0f);
    }

    // LEFT WALL //
    {
        b2BodyDef wallBodyDef;
        wallBodyDef.position.Set(leftWallRect.x(), leftWallRect.y());

        leftWallBody = world.CreateBody(&wallBodyDef);

        b2PolygonShape wallBox;
        wallBox.SetAsBox(leftWallRect.width()/2, leftWallRect.height()/2);

        leftWallBody->CreateFixture(&wallBox, 0.0f);
    }

    // RIGHT WALL //
    {
        b2BodyDef wallBodyDef;
        wallBodyDef.position.Set(rightWallRect.x(), rightWallRect.y());

        rightWallBody = world.CreateBody(&wallBodyDef);

        b2PolygonShape wallBox;
        wallBox.SetAsBox(rightWallRect.width()/2, rightWallRect.height()/2);

        rightWallBody->CreateFixture(&wallBox, 0.0f);
    }

    // CEILING //
    {
        b2BodyDef ceilBodyDef;
        ceilBodyDef.position.Set(ceilRect.x(), ceilRect.y());
        ceilBody = world.CreateBody(&ceilBodyDef);

        b2PolygonShape ceilBox;
        ceilBox.SetAsBox(ceilRect.width()/2, ceilRect.height()/2);

        b2FixtureDef ceilFixtureDef;
        ceilFixtureDef.shape = &ceilBox;
        ceilFixtureDef.isSensor = true;

        ceilBody->CreateFixture(&ceilFixtureDef);
    }

    // ICE CUBE //
    {
        // Define the dynamic body. We set its position and call the body factory.
        b2BodyDef iceBodyDef;
        iceBodyDef.type = b2_dynamicBody;
        iceBodyDef.position.Set(iceRect.x(), iceRect.y());
        iceBodyDef.angle = M_PI * 1/6.0;
        iceBody = world.CreateBody(&iceBodyDef);

        // Define another box shape for our dynamic body.
        b2PolygonShape iceBox;
        iceBox.SetAsBox(iceRect.width()/2, iceRect.height()/2);

        b2FixtureDef iceFixtureDef;
        iceFixtureDef.shape = &iceBox;
        iceFixtureDef.density = 0.9f;
        iceFixtureDef.friction = 0.1f;
        iceFixtureDef.restitution = 0.1;

        iceBody->CreateFixture(&iceFixtureDef);
    }

    // FLUID //
    {
        b2BodyDef fluidBodyDef;
        fluidBodyDef.type = b2_dynamicBody;
        fluidBodyDef.position.Set(fluidRect.x(), fluidRect.y());
        fluidBody = world.CreateBody(&fluidBodyDef);

        b2PolygonShape fluidBox;
        fluidBox.SetAsBox(fluidRect.width()/2, fluidRect.height()/2);

        b2FixtureDef fluidFixtureDef;
        fluidFixtureDef.shape = &fluidBox;
        fluidFixtureDef.isSensor = true;
        fluidFixtureDef.density = 1.0f;

        fluidBody->CreateFixture(&fluidFixtureDef);

        fluidBody->SetGravityScale(0);
        fluidBody->SetLinearVelocity(b2Vec2(0,-2));
    }

    // load images (solid colors)
    iceImage = QImage(iceRect.width()*scaleFactor, iceRect.height()*scaleFactor, QImage::Format_RGB16);
    iceImage.fill(QColor(220, 220, 250, 100));
    floorImage = QImage(floorRect.width()*scaleFactor, floorRect.height()*scaleFactor, QImage::Format_RGB16);
    floorImage.fill(QColor(0,0,0,150));
    wallImage = QImage(leftWallRect.width()*scaleFactor, leftWallRect.height()*scaleFactor, QImage::Format_RGB16);
    wallImage.fill(QColor(0,0,0,150));
    ceilImage = QImage(ceilRect.width()*scaleFactor, ceilRect.height()*scaleFactor, QImage::Format_RGB16);
    ceilImage.fill(QColor(255,255,255,150));
    fluidImage = QImage(fluidRect.width()*scaleFactor, fluidRect.height()*scaleFactor, QImage::Format_RGB16);
    fluidImage.fill(QColor(217, 92, 92, 100));

    connect(&timer, &QTimer::timeout, this, &CocktailWidget::updateWorld);
    timer.start(10);
}

CocktailWidget::~CocktailWidget(){
    //    delete allIceInFluid; // list of all ice cubes that are currently floating in fluid
    delete overflowListener;
}

// ///// //
// MODEL //
// ///// //
void CocktailWidget::updateWorld() {

    // iterative, assumes multiple ice cubes
    //    foreach(b2Body* tempIceBody, allIceInFluid){

    //        b2Fixture iceFixt = tempIceBody->GetFixtureList()[0];
    //        b2Fixture fluidFixt = fluidBody->GetFixtureList()[0];

    //        b2Vec2 buoyancyForce = calcBuoyancyForce(iceFixt, fluidFixt); // params: box, fluid
    //        tempIceBody->ApplyForceToCenter(buoyancyForce, true);
    //    }

    // assumes one ice cube
    if(isIceInFluid){
        b2Fixture iceFixt = iceBody->GetFixtureList()[0];
        b2Fixture fluidFixt = fluidBody->GetFixtureList()[0];

        b2Vec2 buoyancyForce = calcBuoyancyForce(iceFixt, fluidFixt); // params: box, fluid
        iceBody->ApplyForceToCenter(buoyancyForce, true);
        b2Vec2 dragForce = calcDragForce(iceFixt, fluidFixt);
        iceBody->ApplyForceToCenter(dragForce, true);

    }

    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/60.0, 6, 2);

    update();
}

// helper
// calculates the buoyancy force exerted by a fluid on a box
b2Vec2 CocktailWidget::calcBuoyancyForce(b2Fixture box, b2Fixture fluid) {
    // FIND OVERLAPPING AREA (i.e. the portion of box in the fluid)
    double boxArea = box.GetAABB(0).GetExtents().LengthSquared() * 4;
    double boxHeight = box.GetAABB(0).GetExtents().y * 2;
    double boxBottomY = box.GetAABB(0).GetCenter().y + box.GetAABB(0).GetExtents().y;
    double fluidTopY = fluid.GetAABB(0).GetCenter().y - fluid.GetAABB(0).GetExtents().y;

    double portionSubmerged = (boxBottomY - fluidTopY) / boxHeight;
    if(portionSubmerged > 1) { portionSubmerged = 1; }
    else if(portionSubmerged < 0) { portionSubmerged = 0; }

    double overlappingArea = boxArea * portionSubmerged;

    // CALCULATE FORCE
    double displacedMass = fluid.GetDensity() * overlappingArea;
    b2Vec2 gravity = b2Vec2(0, 10);
    b2Vec2 buoyancyForce = displacedMass * -gravity;

    return buoyancyForce;
}

// helper
// calculates the drag experienced by a box
b2Vec2 CocktailWidget::calcDragForce(b2Fixture box, b2Fixture fluid) {
    // snippet taken from: http://www.iforce2d.net/b2dtut/buoyancy
    // used with modifications

    //find relative velocity between object and fluid
    b2Vec2 velDir = box.GetBody()->GetLinearVelocity();
    float vel = velDir.Normalize();

    //apply simple linear drag
    float dragMag = fluid.GetDensity() * vel * vel;
    b2Vec2 dragForce = dragMag * -velDir;

    return dragForce;
    // end of snippet
}



// contact listener
void CocktailWidget::OverflowListener::BeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    bool isAIce = fixtureA->GetBody()->GetType() == b2_dynamicBody && !(fixtureA->IsSensor());
    bool isBIce = fixtureB->GetBody()->GetType() == b2_dynamicBody && !(fixtureB->IsSensor());

    bool isAFluid = fixtureA->GetBody()->GetType() == b2_dynamicBody && fixtureA->IsSensor();
    bool isBFluid = fixtureB->GetBody()->GetType() == b2_dynamicBody && fixtureB->IsSensor();

    bool isACeil = !(fixtureA->GetBody()->GetType() == b2_dynamicBody) && fixtureA->IsSensor();
    bool isBCeil = !(fixtureB->GetBody()->GetType() == b2_dynamicBody) && fixtureB->IsSensor();


    // if fluid gets to the top of the cup, stop raising fluid
    if (isACeil && isBFluid) {
        fixtureB->GetBody()->SetLinearVelocity(b2Vec2(0,0));
    } else if (isBCeil && isAFluid) {
        fixtureA->GetBody()->SetLinearVelocity(b2Vec2(0,0));
    }

    // if ice collides with fluid, remember that
    // (later, in update, apply buoyancy)
    if (isAIce && isBFluid) {
        isIceInFluid = true;
        //        allIceInFluid.insert(fixtureB->GetBody());
    } else if (isBIce && isAFluid) {
        isIceInFluid = true;
        //        allIceInFluid.insert(fixtureA->GetBody());
    }
}

void CocktailWidget::OverflowListener::EndContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    bool isAIce = fixtureA->GetBody()->GetType() == b2_dynamicBody && !(fixtureA->IsSensor());
    bool isBIce = fixtureB->GetBody()->GetType() == b2_dynamicBody && !(fixtureB->IsSensor());

    bool isAFluid = fixtureA->GetBody()->GetType() == b2_dynamicBody && fixtureA->IsSensor();
    bool isBFluid = fixtureB->GetBody()->GetType() == b2_dynamicBody && fixtureB->IsSensor();

    // if ice ends contact with fluid, remember that
    // (later, in update, stop applying buoyancy)
    if ( isAFluid && isBIce) { // fluid + ice collision
        isIceInFluid = false;
        //        allIceInFluid.remove(fixtureB->GetBody());
    } else if ( isBFluid && isAIce ) { // fluid + ice collision
        isIceInFluid = false;
        //        allIceInFluid.remove(fixtureA->GetBody());
    }
}

// //// //
// VIEW //
// //// //
void CocktailWidget::paintEvent(QPaintEvent *) {
    // Create a painter
    QPainter painter(this);

    // bg
    QImage bgImage = QImage(this->width(),this->height(), QImage::Format_RGB16);
    bgImage.fill(QColor(186, 140, 99, 255));
    painter.drawImage(0, 0, bgImage);

    // ceil
    b2Vec2 ceilPos_TopLeft = getTopLeftPointOfRectBody(ceilBody);
    painter.drawImage(ceilPos_TopLeft.x*scaleFactor, ceilPos_TopLeft.y*scaleFactor, ceilImage);

    // ice (drawn w/ rotation)
    b2Vec2 icePos = iceBody->GetPosition();
    double iceHalfWidth = iceBody->GetFixtureList()[0].GetAABB(0).GetExtents().x;
    double iceHalfHeight = iceBody->GetFixtureList()[0].GetAABB(0).GetExtents().y;
    double iceAngle = iceBody->GetAngle() / M_PI * 180; // convert from radians to degrees
    painter.save();
    painter.translate(icePos.x*scaleFactor, icePos.y*scaleFactor);
    painter.rotate(iceAngle);
    painter.drawImage(-iceHalfWidth*scaleFactor, -iceHalfHeight*scaleFactor, iceImage);// the painter is transformed, icePos is the origin, draw from the topleft corner
    painter.restore();

    // fluid
    b2Vec2 fluidPos_TopLeft = getTopLeftPointOfRectBody(fluidBody);
    painter.drawImage(fluidPos_TopLeft.x*scaleFactor, fluidPos_TopLeft.y*scaleFactor, fluidImage);

    // floor
    b2Vec2 floorPos_TopLeft = getTopLeftPointOfRectBody(floorBody);
    painter.drawImage(floorPos_TopLeft.x*scaleFactor, floorPos_TopLeft.y*scaleFactor, floorImage);

    // walls
    b2Vec2 leftWallPos_TopLeft = getTopLeftPointOfRectBody(leftWallBody);
    painter.drawImage(leftWallPos_TopLeft.x*scaleFactor, leftWallPos_TopLeft.y*scaleFactor, wallImage);
    b2Vec2 rightWallPos_TopLeft = getTopLeftPointOfRectBody(rightWallBody);
    painter.drawImage(rightWallPos_TopLeft.x*scaleFactor, rightWallPos_TopLeft.y*scaleFactor, wallImage);

    painter.end();
}

b2Vec2 CocktailWidget::getTopLeftPointOfRectBody(b2Body *body){
    b2Vec2 bodyPos = body->GetPosition();
    double bodyHalfWidth = body->GetFixtureList()[0].GetAABB(0).GetExtents().x;
    double bodyHalfHeight = body->GetFixtureList()[0].GetAABB(0).GetExtents().y;
    b2Vec2 bodyPos_TopLeft = b2Vec2(bodyPos.x - bodyHalfWidth, bodyPos.y - bodyHalfHeight);

    return bodyPos_TopLeft;
}

// when left is clicked, move ice towards the mouse
void CocktailWidget::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        b2Vec2 mousePos = b2Vec2( event->position().x()/scaleFactor, event->position().y()/scaleFactor );
        b2Vec2 icePos = iceBody->GetPosition();

        b2Vec2 velocity = mousePos - icePos;
        iceBody->SetLinearVelocity(velocity);
    }
}
