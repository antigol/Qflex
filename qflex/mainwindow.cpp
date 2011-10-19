#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
#include <poppler-qt4.h>

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
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(itemDoubleClick(QTreeWidgetItem*,int)));
    connect(&qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(documentDownloaded(QNetworkReply*)));

    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    disconnect(&qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(documentDownloaded(QNetworkReply*)));
    connect(&qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
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
    disconnect(&qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    connect(&qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(documentDownloaded(QNetworkReply*)));

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
            branch->setData(0, Qt::UserRole + 2, xml.attributes().value("name").toString());
            xml.skipCurrentElement();
        } else {
            readAll(branch);
        }
    }
}

void MainWindow::itemChanged()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    //ui->label->setText(item->data(0, Qt::UserRole + 1).toString() + "(" + item->data(0, Qt::UserRole + 2).toString() + ")");

    QUrl url("http://cmspc46.epfl.ch/20112012Data/Exercices/" + item->data(0, Qt::UserRole + 1).toString());
    qnam.get(QNetworkRequest(url));
}

void MainWindow::documentDownloaded(QNetworkReply *reply)
{
    QString extention = reply->url().toString().section('.', -1);

    qDebug("Download finished, extention = %s", extention.toAscii().data());

    if (extention.compare("pdf", Qt::CaseInsensitive) == 0) {
        QFile file(QDir::homePath() + "/.qflex.pdf");
        if (file.open(QIODevice::ReadWrite)) {
            file.write(reply->readAll());
            file.close();
            Poppler::Document *doc = Poppler::Document::load(QDir::homePath() + "/.qflex.pdf");
                image = doc->page(0)->renderToImage(
                            1.0 * physicalDpiX(),
                            1.0 * physicalDpiY());
                ui->label->setPixmap(QPixmap::fromImage(image));
        }
    } else if (extention.compare("html", Qt::CaseInsensitive) == 0) {

    } else {
        image.load(reply, extention.toAscii().data());

        ui->label->setPixmap(QPixmap::fromImage(image));
    }
}

void MainWindow::itemDoubleClick(QTreeWidgetItem *item,int)
{
    QDesktopServices::openUrl(QUrl(QString("http://cmspc46.epfl.ch/20112012Data/Exercices/%1").arg(item->data(0, Qt::UserRole + 1).toString())));
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
        while (above->childCount() != 0) {
            above = above->child(above->childCount() - 1);
        }
        item = above;
    } else {
        item = above;
    }

    while (item != 0) {
        if (!item->data(0, Qt::UserRole + 1).isNull()) {
            ui->treeWidget->setCurrentItem(item);
            return;
        }

        QTreeWidgetItem *above = ui->treeWidget->itemAbove(item);
        if (above != 0 && item->parent() != above && above->childCount() != 0) {
            while (above->childCount() != 0) {
                above = above->child(above->childCount() - 1);
            }
            item = above;
        } else {
            item = above;
        }

    }
}

