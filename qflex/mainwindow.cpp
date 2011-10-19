#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->actionMettre_jour->setShortcut(QKeySequence("Ctrl+U"));
    ui->action_Suivant->setShortcut(QKeySequence("Ctrl+K"));
    ui->action_Pr_c_dant->setShortcut(QKeySequence("Ctrl+J"));

    connect(ui->actionMettre_jour, SIGNAL(triggered()), this, SLOT(update()));
    connect(ui->action_Suivant, SIGNAL(triggered()), this, SLOT(nextDocument()));
    connect(ui->action_Pr_c_dant, SIGNAL(triggered()), this, SLOT(previousDocument()));
    connect(ui->treeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(itemChanged()));
    connect(&qnam, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    qnam.get(QNetworkRequest(QUrl("http://cmspc46.epfl.ch/20112012Data/Exercices/20112012semesters.xml")));
    /*
    QFile file("20112012semesters.xml");
    file.open(QIODevice::ReadOnly);
    xml.addData(file.readAll());

    if (xml.readNextStartElement()) {
        if (xml.name() == "semesters") {
            readSemesters();
        }
    }
*/
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    xml.addData(reply->readAll());

    if (xml.readNextStartElement()) {
        if (xml.name() == "semesters") {
            readSemesters();
        }
    }
}

QTreeWidgetItem *MainWindow::createChildItem(QTreeWidgetItem *item)
{
    QTreeWidgetItem *childItem;
    if (item) {
        childItem = new QTreeWidgetItem(item);
    } else {
        childItem = new QTreeWidgetItem(ui->treeWidget);
    }
    childItem->setData(0, Qt::UserRole, xml.name().toString());
    return childItem;
}

void MainWindow::readSemesters()
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "semesters");

    // balise principale
    while (xml.readNextStartElement()) {
        if (xml.name() == "semesterentry") {
            readAll(0);
        }
    }
}

void MainWindow::readAll(QTreeWidgetItem *item)
{
    QTreeWidgetItem *branch = createChildItem(item);

    if (xml.name() == "semesterentry") {
        ui->treeWidget->setItemExpanded(branch, true);
    }

    while (xml.readNextStartElement()) {
        if (xml.name() == "name") {
            QString textName = xml.readElementText();
            branch->setText(0, textName);
        } else if (xml.name() == "address") {
            branch->setData(0, Qt::UserRole + 1, xml.readElementText());
        } else if (xml.name() == "type") {
            branch->setData(0, Qt::UserRole + 2, xml.readElementText()); //! FIXME : UserRole + 2 ne fonctionne pas
        } else {
            readAll(branch);
        }
    }
}

void MainWindow::itemChanged()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    ui->labelAddress->setText(item->data(0, Qt::UserRole + 1).toString());
}

void MainWindow::nextDocument()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if (item == 0)
        return;

    if (item->childCount() != 0)
        item = item->child(0);
    else
        item = ui->treeWidget->itemBelow(item);

    while (item != 0) {
        if (!item->data(0, Qt::UserRole + 1).isNull()) {
            ui->treeWidget->setCurrentItem(item);
            return;
        }

        if (item->childCount() != 0)
            item = item->child(0);
        else
            item = ui->treeWidget->itemBelow(item);
    }
}

void MainWindow::previousDocument()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if (item == 0)
        return;

    QTreeWidgetItem *above = ui->treeWidget->itemAbove(item);
    if (above != 0 && item->parent() != above && above->childCount() != 0) {
        item = above->child(above->childCount() - 1);
    } else {
        item = above;
    }

    while (item != 0) {
        if (!item->data(0, Qt::UserRole + 1).isNull()) {
            ui->treeWidget->setCurrentItem(item);
            return;
        }

        if (above != 0 && item->parent() != above && above->childCount() != 0) {
            item = above->child(above->childCount() - 1);
        } else {
            item = above;
        }
    }
}

