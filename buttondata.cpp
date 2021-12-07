#include "buttondata.h"
#include <QRect>
#include <QSize>

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
