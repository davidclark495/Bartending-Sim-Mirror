#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <Qt>

//Class that allows for registering mouse click events inside a label
class clickableLabel : public QLabel {
Q_OBJECT
public:
    explicit clickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~clickableLabel();

private:

signals:
    void clicked(const QPoint&);
    void released();


protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

};

#endif // CLICKABLELABEL_H

