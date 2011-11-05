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

const QList<QKeySequence> & OptionDialog::nextDocument()
{
    return ui->lineEdit_ds->keySequence();
}

const QList<QKeySequence> & OptionDialog::previousDocument()
{
    return ui->lineEdit_dp->keySequence();
}

const QList<QKeySequence> & OptionDialog::nextPage()
{
    return ui->lineEdit_ps->keySequence();
}

const QList<QKeySequence> & OptionDialog::previousPage()
{
    return ui->lineEdit_pp->keySequence();
}
