#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
#include <poppler-qt4.h>
#include <QMessageBox>
#include <QDebug>
#include <QHash>
#include <QString>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    reply(0)
{    
    ui->setupUi(this);

    ui->actionMettre_jour->setShortcut(QKeySequence("F5"));
    ui->action_Plein_cran->setShortcut(QKeySequence("F11"));
    ui->action_Suivant->setShortcut(QKeySequence("K"));
    ui->action_Pr_c_dant->setShortcut(QKeySequence("J"));
    ui->action_Quitter->setShortcut(QKeySequence("Ctrl+Q"));

    timer.setInterval(100);
    timer.setSingleShot(true);
    connect(&timer, SIGNAL(timeout()), this, SLOT(refreshDocument()));
    connect(ui->actionMettre_jour, SIGNAL(triggered()), this, SLOT(updateXml()));
    connect(ui->action_Suivant, SIGNAL(triggered()), this, SLOT(nextDocument()));
    connect(ui->action_Pr_c_dant, SIGNAL(triggered()), this, SLOT(previousDocument()));
    connect(ui->action_Plein_cran, SIGNAL(triggered()), this, SLOT(fullscreen()));
    connect(ui->action_Quitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->treeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelected()));
    connect(&qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(documentDownloaded(QNetworkReply*)));

//    showDocuments = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateXml()
{
    if (reply != 0) {
        reply->abort();
    }

    disconnect(&qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(documentDownloaded(QNetworkReply*)));
    connect(&qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(xmlFileDownloaded(QNetworkReply*)));

    reply = qnam.get(QNetworkRequest(QUrl("http://cmspc46.epfl.ch/20112012Data/Exercices/20112012semesters.xml")));

    statusBar()->showMessage(QString::fromUtf8("Téléchargement du fichier xml"));
}

void MainWindow::xmlFileDownloaded(QNetworkReply *reply)
{
    disconnect(&qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(xmlFileDownloaded(QNetworkReply*)));
    connect(&qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(documentDownloaded(QNetworkReply*)));

    QString key = urlToKey(reply->url().toString());
    QByteArray data;

    if (reply->error() != QNetworkReply::NoError) {
        if (set.contains(key)) {
            data = set.value(key).toByteArray();
            readXmlFile(data);
            statusBar()->showMessage(QString::fromUtf8("Pas de connexion au réseau. Récuperation du fichier xml locale"), 4000);
        } else {
            QMessageBox::warning(this, QString::fromUtf8("Erreur de réseau"), QString::fromUtf8("Erreur de téléchagement %1").arg(reply->errorString()));
        }
    } else {
        data = reply->readAll();
        readXmlFile(data);
        set.setValue(key, data);
        statusBar()->showMessage(QString::fromUtf8("Fichier xml téléchargé"), 4000);
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

void MainWindow::readXmlFile(const QByteArray &data)
{
    ui->treeWidget->clear();
    xml.clear();
    xml.addData(data);

    //    if (ui->actionTout_t_l_charger_la_maj->isChecked()) {
    //        showDocuments = false;
    //        QMessageBox::information(this,"Note aux utilisateurs", QString::fromUtf8("Le téléchargement intégral ralentit l'application pendant qu'il s'effectue. De plus il s'effectue en parti en arrière plan, donc si vous souhaitez le finir totalement, attendez quelque temps selon votre connection"));
    //    }

    if (xml.readNextStartElement()) {
        if (xml.name() == "semesters") {
            while (xml.readNextStartElement()) {
                if (xml.name() == "semesterentry") {
                    readXmlBlock(0);
                }
            }
        }
        ui->treeWidget->setCurrentItem(ui->treeWidget->itemAt(0,0));
    }
    statusBar()->showMessage(QString::fromUtf8("Fichier xml déchifré"), 4000);
}

void MainWindow::readXmlBlock(QTreeWidgetItem *item)
{
    QTreeWidgetItem *branch = createChildItem(item);

    if (xml.name() == "semesterentry") {
        ui->treeWidget->setItemExpanded(branch, true);
    }

    // Quand il tombe sur une balise fermée, readNextStartElement retourne false
    while (xml.readNextStartElement()) {

        if (xml.name() == "name") {
            // Si on tombe sur la balise name on lit son contenu, dufait, on se retrouve sur </name>
            QString textName = xml.readElementText();
            branch->setText(0, textName);

        } else if (xml.name() == "address") {
            // Idem que <name>
            branch->setData(0, Qt::UserRole + 1, xml.readElementText());
        } else if (xml.name() == "type") {
            // O récupère l'attribut de la balise type, puis on saute </skip>
            QString type = xml.attributes().value("name").toString();
            if (!type.isEmpty() && type != "null") {
                branch->setData(0, Qt::UserRole + 2, type);
            }

            xml.skipCurrentElement();
        } else {
            // Si c'est une autre balise, on relance récusivement la méthode
            readXmlBlock(branch);
        }
    }

    //    if (ui->actionTout_t_l_charger_la_maj->isChecked() && item != 0) {
    //        startDownload(item);
    //    }
}

void MainWindow::itemSelected()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();

    //    if (item != 0) {
    //        showDocuments = true;
    //    }
    startDownload(item);

}

void MainWindow::startDownload(QTreeWidgetItem *item)
{
    if (!item->data(0, Qt::UserRole + 2).isNull()) {
        QUrl url("http://cmspc46.epfl.ch/20112012Data/Exercices/" + item->data(0, Qt::UserRole + 1).toString());

        QString key = urlToKey(url.toString());
        if (set.contains(key)) {
            //            if (showDocuments) {
            QByteArray data = set.value(key).toByteArray();
            loadDocument(data, url.toString());
            statusBar()->showMessage(QString::fromUtf8("Document locale %1").arg(url.toString().section('/', -1)), 4000);
            //            }
        } else {
            if (reply != 0)
                reply->abort();

            reply = qnam.get(QNetworkRequest(url));
            statusBar()->showMessage(QString::fromUtf8("Téléchargement de %1...").arg(url.toString().section('/', -1)));
        }
    }
}

void MainWindow::documentDownloaded(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        statusBar()->clearMessage();
        statusBar()->showMessage(QString::fromUtf8("Erreur de téléchargement : %1").arg(reply->errorString()), 4000);
        ui->label->setText(QString::fromUtf8("Erreur de téléchangement"));
        return;
    }

    QByteArray data = reply->readAll();
    QString url = reply->url().toString();

    set.setValue(urlToKey(url), data);

    //    if (showDocuments)
    loadDocument(data, url);

    statusBar()->showMessage(QString::fromUtf8("Document téléchangé %1").arg(url.section('/', -1)), 4000);
}

void MainWindow::loadDocument(const QByteArray &data, const QString &url)
{
    QString extention = url.section('.', -1);
    pdfdata.clear();

    if (extention.compare("pdf", Qt::CaseInsensitive) == 0) {
        pdfdata = data;
    } else if (extention.compare("html", Qt::CaseInsensitive) == 0) {

    } else {
        image.load(data, extention.toAscii().data());
    }

    refreshDocument();
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
        if (!item->data(0, Qt::UserRole + 2).isNull()) {
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
        if (!item->data(0, Qt::UserRole + 2).isNull()) {
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

void MainWindow::downloadError()
{
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    timer.start();
    QMainWindow::resizeEvent(e);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    //    qDebug() << e->text() << e->key();
    switch (e->key()) {
    case 16777313: // touche précédent suivant Thinkpad
        previousDocument();
        break;
    case 16777314: // touche document suivant Thinkpad
    case 16777220: // touche retour à la ligne
        nextDocument();
        break;
    }

    QMainWindow::keyPressEvent(e);
}

void MainWindow::refreshDocument()
{
    if (!pdfdata.isEmpty()) {
        Poppler::Document *doc = Poppler::Document::loadFromData(pdfdata);
        doc->setRenderHint(Poppler::Document::TextAntialiasing);
        doc->setRenderHint(Poppler::Document::TextHinting);
        doc->setRenderHint(Poppler::Document::Antialiasing);

        double ratioX = ((double)ui->scrollArea->width() - 22) / doc->page(0)->pageSizeF().width();
        double ratioY = ((double)ui->scrollArea->height() - 22) / doc->page(0)->pageSizeF().height();
        double ratio;
        if (ratioX < ratioY || ratioY < 1.3) {
            ratio = ratioX;
        } else {
            ratio = ratioY;
        }
        ratio *= 72.0;
        image = doc->page(0)->renderToImage(
                    ratio /* physicalDpiX()*/,
                    ratio /* physicalDpiY()*/);
    }

    QPixmap pixmap = QPixmap::fromImage(image);
    ui->label->setPixmap(pixmap);
}

void MainWindow::fullscreen()
{
    setWindowState(windowState() ^ Qt::WindowFullScreen);
}

QString MainWindow::urlToKey(const QString &url) const
{
    return QString::number(qHash(url), 16);
}

void MainWindow::downloadAll()
{
}

