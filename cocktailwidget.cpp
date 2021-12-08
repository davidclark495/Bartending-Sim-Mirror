#include "cocktailwidget.h"
#include <QPainter>
#include <QDebug>
#include <iostream>


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

    // set positions, sizes (used to set box2d values)
    QRect ceilRect = QRect(10, 2, 10, 1);
    QRect floorRect = QRect(10, 24, 10, 4);
    QRect fluidRect = QRect(10, 30, 10, 8);
    QRect iceRect = QRect(12, 14, 4, 4);

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

        // Define the ground box shape.
        b2PolygonShape floorBox;

        // The extents are the half-widths of the box.
        floorBox.SetAsBox(floorRect.width()/2, floorRect.height()/2);

        // Add the ground fixture to the ground body.
        floorBody->CreateFixture(&floorBox, 0.0f);
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
        iceBodyDef.angle = M_PI * 1/6;
        iceBody = world.CreateBody(&iceBodyDef);

        // Define another box shape for our dynamic body.
        b2PolygonShape iceBox;
        iceBox.SetAsBox(iceRect.width()/2, iceRect.height()/2);

        b2FixtureDef iceFixtureDef;
        iceFixtureDef.shape = &iceBox;
        iceFixtureDef.density = 1.0f;
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
    ceilImage = QImage(ceilRect.width()*scaleFactor, ceilRect.height()*scaleFactor, QImage::Format_RGB16);
    ceilImage.fill(QColor(255,255,255,150));
    fluidImage = QImage(fluidRect.width()*scaleFactor, fluidRect.height()*scaleFactor, QImage::Format_RGB16);
    fluidImage.fill(QColor(217, 130, 63, 100));

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
    }

    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/60.0, 6, 2);

    update();
}

// helper
// calculates the area of a box that is below a given waterline
b2Vec2 CocktailWidget::calcBuoyancyForce(b2Fixture box, b2Fixture fluid) {

    // FIND OVERLAPPING AREA (i.e. the portion of box in the fluid)
    double boxArea = box.GetAABB(0).GetExtents().LengthSquared() * 4;
    double boxHeight = box.GetAABB(0).GetExtents().y * 2;
    double boxBottomY = box.GetAABB(0).GetCenter().y + box.GetAABB(0).GetExtents().y;
    double fluidTopY = fluid.GetAABB(0).GetCenter().y - fluid.GetAABB(0).GetExtents().y;

    double portionSubmerged = (boxBottomY - fluidTopY) / boxHeight;
    if(portionSubmerged > 1) { portionSubmerged = 1; }
    else if(portionSubmerged < 0) { portionSubmerged = 0; }
    std::cout << "Percent of Ice submerged: " << portionSubmerged * 100 << std::endl;

    double overlappingArea = boxArea * portionSubmerged;

    // MORE MATH
    double displacedMass = fluid.GetDensity() * overlappingArea;
    b2Vec2 gravity = b2Vec2(0, 10);
    b2Vec2 buoyancyForce = displacedMass * -gravity;

    return buoyancyForce;
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

    // if ice ends contact with fluid, remember that
    // (later, in update, stop applying buoyancy)
    if ( fixtureA->IsSensor() && fixtureB->GetBody()->GetType() == b2_dynamicBody) { // fluid + ice collision (and other false signals)
        isIceInFluid = false;
        //        allIceInFluid.remove(fixtureB->GetBody());
    } else if ( fixtureB->IsSensor() && fixtureA->GetBody()->GetType() == b2_dynamicBody) { // fluid + ice collision (and other false signals)
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

    // ceil
    b2Vec2 ceilPos = ceilBody->GetPosition();
    painter.drawImage(ceilPos.x*scaleFactor, ceilPos.y*scaleFactor, ceilImage);

    // debug
//    {
//        // draw rect based on box2d world
//        b2Fixture ceilFix = ceilBody->GetFixtureList()[0];
//        b2AABB ceilFixBox = ceilFix.GetAABB(0);
//        double ceilFixBoxWidth = ceilFixBox.GetExtents().x * 2;
//        double ceilFixBoxHeight = ceilFixBox.GetExtents().y * 2;
//        ceilImage = QImage(ceilFixBoxWidth*scaleFactor, ceilFixBoxHeight*scaleFactor, QImage::Format_RGB16);
//        ceilImage.fill(QColor(255,255,255,150));
//        painter.drawImage((int)(ceilPos.x*scaleFactor), (int)(ceilPos.y*scaleFactor), ceilImage);

//        // draw rect based on stored rect
//        QPoint ceilRectPos = ceilRect.center();
//        ceilImage = QImage(ceilRect.width()*scaleFactor, ceilRect.height()*scaleFactor, QImage::Format_RGB16);
//        ceilImage.fill(QColor(255,255,255,50));
//        painter.drawImage((int)(ceilRectPos.x()*scaleFactor), (int)(ceilRectPos.y()*scaleFactor), ceilImage);
//    }

    // ice (drawn w/ rotation)
    b2Vec2 icePos = iceBody->GetPosition();
//    painter.drawImage(icePos.x*scaleFactor, icePos.y*scaleFactor, iceImage); // draw without rotation
    float iceAngle = iceBody->GetAngle() / M_PI * 180; // convert from radians to degrees
    painter.save();
    painter.translate(icePos.x*scaleFactor, icePos.y*scaleFactor);
    painter.rotate(iceAngle);
    painter.drawImage(0, 0, iceImage);// the painter is transformed, icePos is the origin
    painter.restore();

    // fluid
    b2Vec2 fluidPos = fluidBody->GetPosition();
    painter.drawImage(fluidPos.x*scaleFactor, fluidPos.y*scaleFactor, fluidImage);

    // floor
    b2Vec2 floorPos = floorBody->GetPosition();
    painter.drawImage(floorPos.x*scaleFactor, floorPos.y*scaleFactor, floorImage);

    painter.end();
}

void CocktailWidget::printPos(QString label, b2Vec2 position){
    std::cout << printf("%s %4.2f %4.2f ", label.data(), position.x, position.y) << std::endl;

}
