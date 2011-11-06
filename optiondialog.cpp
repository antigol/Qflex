#include "optiondialog.h"
#include "ui_optiondialog.h"

OptionDialog::OptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionDialog)
{
    ui->setupUi(this);
}

OptionDialog::~OptionDialog()
{
    delete ui;
}

const QList<QKeySequence> & OptionDialog::nextDocument() const
{
    return ui->lineEdit_ds->keySequences();
}

const QList<QKeySequence> & OptionDialog::previousDocument() const
{
    return ui->lineEdit_dp->keySequences();
}

const QList<QKeySequence> & OptionDialog::nextPage() const
{
    return ui->lineEdit_ps->keySequences();
}

const QList<QKeySequence> & OptionDialog::previousPage() const
{
    return ui->lineEdit_pp->keySequences();
}

void OptionDialog::setNextDocument(const QList<QKeySequence> &list)
{
    ui->lineEdit_ds->setKeySequences(list);
}

void OptionDialog::setPreviousDocument(const QList<QKeySequence> &list)
{
    ui->lineEdit_dp->setKeySequences(list);
}

void OptionDialog::setNextPage(const QList<QKeySequence> &list)
{
    ui->lineEdit_ps->setKeySequences(list);
}

void OptionDialog::setPreviousPage(const QList<QKeySequence> &list)
{
    ui->lineEdit_pp->setKeySequences(list);
}
