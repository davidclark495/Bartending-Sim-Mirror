#ifndef BUTTONDATA_H
#define BUTTONDATA_H
#include <QRect>
#include <QSize>
#include <QAbstractButton>

class buttonData
{
public:
    buttonData() {}
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
