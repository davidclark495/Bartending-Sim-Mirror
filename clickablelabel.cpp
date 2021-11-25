#include "clickablelabel.h"
#include <QMouseEvent>
#include "stateEnums.h"


//Create a label object that can register click events
clickableLabel::clickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {
}

clickableLabel::~clickableLabel() {}

void clickableLabel::mousePressEvent(QMouseEvent* event) {
    const QPoint p = event->pos();
    emit clicked(p);
}
void clickableLabel::mouseReleaseEvent(QMouseEvent* event) {
    emit released();
}

Ingredients clickableLabel::getIngredient() const
{
    return thisIngredient;
}

void clickableLabel::setIngredient(Ingredients ing)
{
    thisIngredient = ing;
}
