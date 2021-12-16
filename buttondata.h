#ifndef BUTTONDATA_H
#define BUTTONDATA_H
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
 *  Style Checked by : Zachary Atherton - u1023217
 **/
#include <QRect>
#include <QSize>
#include <QAbstractButton>

//stores original location, size, icon size of a given button.
class buttonData
{
public:
    buttonData() {}
    // initialize using an abstract button
    buttonData(QAbstractButton* button);

    const QRect &getGeometry() const;
    const QSize &getButtonSize() const;
    const QSize &getIconSize() const;

private:
    QRect geometry;
    QSize buttonSize;
    QSize iconSize;
};

#endif // BUTTONDATA_H
