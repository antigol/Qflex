#ifndef TREE_H
#define TREE_H

#include <QTreeWidget>

class Tree : public QTreeWidget
{
    Q_OBJECT
public:
    explicit Tree(QWidget *parent = 0);

protected:
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // TREE_H
