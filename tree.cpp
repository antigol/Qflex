#include "tree.h"
#include <QKeyEvent>

Tree::Tree(QWidget *parent) :
    QTreeWidget(parent)
{
}

void Tree::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_Up:
    case Qt::Key_Right:
    case Qt::Key_Down:
        QTreeWidget::keyPressEvent(event);
        break;
    default:
        event->ignore();
        break;
    }
}
