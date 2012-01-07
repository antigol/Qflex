/********************************************************************************
** Form generated from reading UI file 'optiondialog.ui'
**
** Created: Fri Jan 6 15:51:15 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONDIALOG_H
#define UI_OPTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "keylineedit.h"

QT_BEGIN_NAMESPACE

class Ui_OptionDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QFormLayout *formLayout;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    KeyLineEdit *lineEdit_dp;
    QHBoxLayout *horizontalLayout;
    KeyLineEdit *lineEdit_ds;
    QLabel *label_4;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_4;
    KeyLineEdit *lineEdit_pp;
    QHBoxLayout *horizontalLayout_3;
    KeyLineEdit *lineEdit_ps;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *OptionDialog)
    {
        if (OptionDialog->objectName().isEmpty())
            OptionDialog->setObjectName(QString::fromUtf8("OptionDialog"));
        OptionDialog->resize(352, 282);
        verticalLayout = new QVBoxLayout(OptionDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_5 = new QLabel(OptionDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout->addWidget(label_5);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(3, QFormLayout::LabelRole, verticalSpacer);

        label_2 = new QLabel(OptionDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        label = new QLabel(OptionDialog);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEdit_dp = new KeyLineEdit(OptionDialog);
        lineEdit_dp->setObjectName(QString::fromUtf8("lineEdit_dp"));

        horizontalLayout_2->addWidget(lineEdit_dp);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit_ds = new KeyLineEdit(OptionDialog);
        lineEdit_ds->setObjectName(QString::fromUtf8("lineEdit_ds"));

        horizontalLayout->addWidget(lineEdit_ds);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout);

        label_4 = new QLabel(OptionDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        label_3 = new QLabel(OptionDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lineEdit_pp = new KeyLineEdit(OptionDialog);
        lineEdit_pp->setObjectName(QString::fromUtf8("lineEdit_pp"));

        horizontalLayout_4->addWidget(lineEdit_pp);


        formLayout->setLayout(4, QFormLayout::FieldRole, horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lineEdit_ps = new KeyLineEdit(OptionDialog);
        lineEdit_ps->setObjectName(QString::fromUtf8("lineEdit_ps"));

        horizontalLayout_3->addWidget(lineEdit_ps);


        formLayout->setLayout(5, QFormLayout::FieldRole, horizontalLayout_3);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(OptionDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(OptionDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), OptionDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), OptionDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(OptionDialog);
    } // setupUi

    void retranslateUi(QDialog *OptionDialog)
    {
        OptionDialog->setWindowTitle(QApplication::translate("OptionDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("OptionDialog", "Raccoursis claviers", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("OptionDialog", "Document pr\303\251c\303\251dent", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("OptionDialog", "Document suivant", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("OptionDialog", "Page pr\303\251c\303\251dente", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("OptionDialog", "Page suivante", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OptionDialog: public Ui_OptionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONDIALOG_H
