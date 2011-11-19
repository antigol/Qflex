#include "keylineedit.h"
#include <QKeyEvent>
#include <QDebug>

KeyLineEdit::KeyLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

void KeyLineEdit::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Tab) {
        e->ignore();
        QLineEdit::keyPressEvent(e);
        return;
    }
    if (e->key() == Qt::Key_Backspace) {
        e->accept();
        clear();
        return;
    }

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

    e->accept();
}

void KeyLineEdit::setKeySequences(const QList<QKeySequence> &list)
{
    clear();

    ks = list;

    QString str;
    for (int i = 0; i < ks.size(); ++i) {
        str += (str.isEmpty()) ? ks[i].toString() : ", "+ks[i].toString();
    }
    setText(str);
}

const QList<QKeySequence> &KeyLineEdit::keySequences() const
{
    return ks;
}

void KeyLineEdit::clear()
{
    ks.clear();
    QLineEdit::clear();
}

