#ifndef KEYLINEEDIT_H
#define KEYLINEEDIT_H

#include <QLineEdit>
#include <QKeySequence>

class KeyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit KeyLineEdit(QWidget *parent = 0);

    const QList<QKeySequence> &keySequence() const;

public slots:
    void clear();

protected:
    void keyPressEvent(QKeyEvent *);

private:
    QList<QKeySequence> ks;
};

#endif // KEYLINEEDIT_H
