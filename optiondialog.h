#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>
#include <QKeySequence>

namespace Ui {
    class OptionDialog;
}

class OptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionDialog(QWidget *parent = 0);
    ~OptionDialog();

    void setNextDocument(const QList<QKeySequence> &list);
    void setPreviousDocument(const QList<QKeySequence> &list);
    void setNextPage(const QList<QKeySequence> &list);
    void setPreviousPage(const QList<QKeySequence> &list);

    const QList<QKeySequence> &nextDocument() const;
    const QList<QKeySequence> &previousDocument() const;
    const QList<QKeySequence> &nextPage() const;
    const QList<QKeySequence> &previousPage() const;

private:
    Ui::OptionDialog *ui;
};

#endif // OPTIONDIALOG_H
