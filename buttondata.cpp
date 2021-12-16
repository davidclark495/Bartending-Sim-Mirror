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
#include <QRect>
#include <QSize>
#include "buttondata.h"

buttonData::buttonData(QAbstractButton* button)
{
    geometry = button->geometry();
    buttonSize = button->size();
    iconSize = button->iconSize();
}

const QRect &buttonData::getGeometry() const
{
    return geometry;
}

const QSize &buttonData::getButtonSize() const
{
    return buttonSize;
}

const QSize &buttonData::getIconSize() const
{
    return iconSize;
}
