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

    const QList<QKeySequence> &nextDocument();
    const QList<QKeySequence> &previousDocument();
    const QList<QKeySequence> &nextPage();
    const QList<QKeySequence> &previousPage();

private:
    Ui::OptionDialog *ui;
};

#endif // OPTIONDIALOG_H
