#include "keylineedit.h"
#include <QKeyEvent>
#include <QDebug>

KeyLineEdit::KeyLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

void KeyLineEdit::keyPressEvent(QKeyEvent *e)
{
    QKeySequence key = QKeySequence(e->modifiers() | e->key());

    QString str = key.toString();

    for (int i = 0; i < str.size(); ++i) {
        if (str[i].category() >= 10 &&
                str[i].category() <= 14) {
            return;
        }
    }

    if (!ks.contains(key)) {
        ks.append(key);

        if (!text().isEmpty())
            setText(text() + ", ");

        setText(text() + str);
    }
}

const QList<QKeySequence> &KeyLineEdit::keySequence() const
{
    return ks;
}

void KeyLineEdit::clear()
{
    ks.clear();
    QLineEdit::clear();
}