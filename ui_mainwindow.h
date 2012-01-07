/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri Jan 6 15:51:15 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QScrollArea>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>
#include "tree.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionMettre_jour;
    QAction *action_Suivant;
    QAction *action_Pr_c_dant;
    QAction *action_Plein_cran;
    QAction *action_Quitter;
    QAction *action_Tout_r_duire;
    QAction *actionT_l_charger_tout_les_documents;
    QAction *action_Exporter;
    QAction *actionModifier_les_sources;
    QAction *actionParam_tres;
    QAction *actionPage_suiva_nte;
    QAction *actionPage_p_r_c_dante;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    Tree *treeWidget;
    QScrollArea *scrollArea;
    QWidget *scrollLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QWebView *webView;
    QMenuBar *menuBar;
    QMenu *menu_Fichier;
    QMenu *menu_Navigation;
    QMenu *menu_Affichage;
    QMenu *menu_Option;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(816, 479);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ico/qflex.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionMettre_jour = new QAction(MainWindow);
        actionMettre_jour->setObjectName(QString::fromUtf8("actionMettre_jour"));
        action_Suivant = new QAction(MainWindow);
        action_Suivant->setObjectName(QString::fromUtf8("action_Suivant"));
        action_Pr_c_dant = new QAction(MainWindow);
        action_Pr_c_dant->setObjectName(QString::fromUtf8("action_Pr_c_dant"));
        action_Plein_cran = new QAction(MainWindow);
        action_Plein_cran->setObjectName(QString::fromUtf8("action_Plein_cran"));
        action_Quitter = new QAction(MainWindow);
        action_Quitter->setObjectName(QString::fromUtf8("action_Quitter"));
        action_Tout_r_duire = new QAction(MainWindow);
        action_Tout_r_duire->setObjectName(QString::fromUtf8("action_Tout_r_duire"));
        actionT_l_charger_tout_les_documents = new QAction(MainWindow);
        actionT_l_charger_tout_les_documents->setObjectName(QString::fromUtf8("actionT_l_charger_tout_les_documents"));
        action_Exporter = new QAction(MainWindow);
        action_Exporter->setObjectName(QString::fromUtf8("action_Exporter"));
        actionModifier_les_sources = new QAction(MainWindow);
        actionModifier_les_sources->setObjectName(QString::fromUtf8("actionModifier_les_sources"));
        actionParam_tres = new QAction(MainWindow);
        actionParam_tres->setObjectName(QString::fromUtf8("actionParam_tres"));
        actionPage_suiva_nte = new QAction(MainWindow);
        actionPage_suiva_nte->setObjectName(QString::fromUtf8("actionPage_suiva_nte"));
        actionPage_p_r_c_dante = new QAction(MainWindow);
        actionPage_p_r_c_dante->setObjectName(QString::fromUtf8("actionPage_p_r_c_dante"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        treeWidget = new Tree(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy);
        treeWidget->setMinimumSize(QSize(220, 0));
        treeWidget->header()->setVisible(false);

        horizontalLayout->addWidget(treeWidget);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollLayout = new QWidget();
        scrollLayout->setObjectName(QString::fromUtf8("scrollLayout"));
        scrollLayout->setGeometry(QRect(0, 0, 76, 399));
        verticalLayout = new QVBoxLayout(scrollLayout);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(scrollLayout);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        scrollArea->setWidget(scrollLayout);

        horizontalLayout->addWidget(scrollArea);

        webView = new QWebView(centralWidget);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setUrl(QUrl("about:blank"));

        horizontalLayout->addWidget(webView);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 816, 25));
        menu_Fichier = new QMenu(menuBar);
        menu_Fichier->setObjectName(QString::fromUtf8("menu_Fichier"));
        menu_Navigation = new QMenu(menuBar);
        menu_Navigation->setObjectName(QString::fromUtf8("menu_Navigation"));
        menu_Affichage = new QMenu(menuBar);
        menu_Affichage->setObjectName(QString::fromUtf8("menu_Affichage"));
        menu_Option = new QMenu(menuBar);
        menu_Option->setObjectName(QString::fromUtf8("menu_Option"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_Fichier->menuAction());
        menuBar->addAction(menu_Affichage->menuAction());
        menuBar->addAction(menu_Navigation->menuAction());
        menuBar->addAction(menu_Option->menuAction());
        menu_Fichier->addAction(actionMettre_jour);
        menu_Fichier->addAction(action_Exporter);
        menu_Fichier->addAction(actionT_l_charger_tout_les_documents);
        menu_Fichier->addAction(action_Quitter);
        menu_Navigation->addAction(action_Tout_r_duire);
        menu_Navigation->addAction(action_Pr_c_dant);
        menu_Navigation->addAction(action_Suivant);
        menu_Navigation->addAction(actionPage_suiva_nte);
        menu_Navigation->addAction(actionPage_p_r_c_dante);
        menu_Affichage->addAction(action_Plein_cran);
        menu_Option->addAction(actionModifier_les_sources);
        menu_Option->addAction(actionParam_tres);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Qflex", 0, QApplication::UnicodeUTF8));
        actionMettre_jour->setText(QApplication::translate("MainWindow", "Mettre \303\240 &jour...", 0, QApplication::UnicodeUTF8));
        action_Suivant->setText(QApplication::translate("MainWindow", "&Suivant", 0, QApplication::UnicodeUTF8));
        action_Pr_c_dant->setText(QApplication::translate("MainWindow", "&Pr\303\251c\303\251dant", 0, QApplication::UnicodeUTF8));
        action_Plein_cran->setText(QApplication::translate("MainWindow", "&Plein \303\251cran", 0, QApplication::UnicodeUTF8));
        action_Quitter->setText(QApplication::translate("MainWindow", "&Quitter", 0, QApplication::UnicodeUTF8));
        action_Tout_r_duire->setText(QApplication::translate("MainWindow", "&Tout r\303\251duire", 0, QApplication::UnicodeUTF8));
        actionT_l_charger_tout_les_documents->setText(QApplication::translate("MainWindow", "T\303\251l\303\251charger tout les documents", 0, QApplication::UnicodeUTF8));
        action_Exporter->setText(QApplication::translate("MainWindow", "&Exporter...", 0, QApplication::UnicodeUTF8));
        actionModifier_les_sources->setText(QApplication::translate("MainWindow", "Modifier les &sources...", 0, QApplication::UnicodeUTF8));
        actionParam_tres->setText(QApplication::translate("MainWindow", "Param\303\250tres...", 0, QApplication::UnicodeUTF8));
        actionPage_suiva_nte->setText(QApplication::translate("MainWindow", "Page s&uivante", 0, QApplication::UnicodeUTF8));
        actionPage_p_r_c_dante->setText(QApplication::translate("MainWindow", "Page p&r\303\251c\303\251dante", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        menu_Fichier->setTitle(QApplication::translate("MainWindow", "&Fichier", 0, QApplication::UnicodeUTF8));
        menu_Navigation->setTitle(QApplication::translate("MainWindow", "&Navigation", 0, QApplication::UnicodeUTF8));
        menu_Affichage->setTitle(QApplication::translate("MainWindow", "&Affichage", 0, QApplication::UnicodeUTF8));
        menu_Option->setTitle(QApplication::translate("MainWindow", "&Option", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
