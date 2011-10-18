#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&qnam, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionMettre_jour_triggered()
{
    qnam.get(QNetworkRequest(QUrl("http://cmspc46.epfl.ch/20112012Data/Exercices/20112012semesters.xml")));
}

void MainWindow::readSemesters()
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "semesters");

    // balise principale
    while (xml.readNextStartElement()) {
        if (xml.name() == "semesterentry") {
            readSemesterentry(0);
        }
    }
}

void MainWindow::readSemesterentry(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "semesterentry");

    QTreeWidgetItem *semester = createChildItem(item);

    ui->treeWidget->setItemExpanded(semester, true);

    while (xml.readNextStartElement()) {
        if (xml.name() == "name") {
            // lire le nom du semetre
            QString textName = xml.readElementText();
            semester->setText(0, textName);
        } else if (xml.name() == "lectureentry") {
            // création d'un enfant
            readLectureentry(semester);
        } else {
            xml.skipCurrentElement();
        }
    }
}

void MainWindow::readLectureentry(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "lectureentry");

    QTreeWidgetItem *lecture = createChildItem(item);

    while (xml.readNextStartElement()) {
        if (xml.name() == "name") {
            // lire le nom de la lecture
            QString textName = xml.readElementText();
            lecture->setText(0, textName);
        } else if (xml.name() == "seriesentry") {
            readSeriesentry(lecture);
        } else {
            xml.skipCurrentElement();
        }
    }
}

void MainWindow::readSeriesentry(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "seriesentry");

    QTreeWidgetItem *series = createChildItem(item);

    while (xml.readNextStartElement()) {
        if (xml.name() == "name") {
            // lire le nom de la serie
            QString textName = xml.readElementText();
            series->setText(0, textName);
        } else if (xml.name() == "exerciceentry") {
            readExercice(series);
        } else {
            xml.skipCurrentElement();
        }
    }
}

void MainWindow::readExercice(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "exerciceentry");

    QTreeWidgetItem *exercice = createChildItem(item);

    while (xml.readNextStartElement()) {
        if (xml.name() == "name") {
            QString textName = xml.readElementText();
            exercice->setText(0, textName);
        } else if (xml.name() == "address") {
            exercice->setData(1, Qt::UserRole, xml.readElementText());
        } else if (xml.name() == "type") {
            exercice->setData(2, Qt::UserRole, xml.readElementText());
        } else if (xml.name() == "methodentry") {
            readMethod(exercice);
        } else {
            xml.skipCurrentElement();
        }
    }

}

void MainWindow::readMethod(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "methodentry");

    QTreeWidgetItem *method = createChildItem(item);

    while (xml.readNextStartElement()) {
        if (xml.name() == "name") {
            QString textName = xml.readElementText();
            method->setText(0, textName);
        } else if (xml.name() == "address") {
            method->setData(1, Qt::UserRole, xml.readElementText());
        } else if (xml.name() == "type") {
            method->setData(2, Qt::UserRole, xml.readElementText());
        } else if (xml.name() == "stepentry") {
            //! FIXME : suite avec readStep
            xml.skipCurrentElement();
        } else {
            xml.skipCurrentElement();
        }
    }

}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui->labelAddress->setText(item->data(1, Qt::UserRole).toString());
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

void MainWindow::replyFinished(QNetworkReply *reply)
{
    xml.addData(reply->readAll());

    if (xml.readNextStartElement()) {
        if (xml.name() == "semesters") {
            readSemesters();
        }
    }
}
