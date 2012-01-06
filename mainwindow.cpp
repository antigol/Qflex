#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
#include <poppler-qt4.h>
#include <QMessageBox>
#include <QDebug>
#include <QHash>
#include <QString>
#include <QKeyEvent>
#include <QProgressBar>
#include <QFileDialog>
#include <QFile>
#include <QInputDialog>
#include "optiondialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    documentType(None),
    downloadingAll(false)
{
    ui->setupUi(this);

    ui->webView->setVisible(false);
    ui->treeWidget->setExpandsOnDoubleClick(true);

    ui->webView->setMinimumSize(ui->scrollArea->minimumSize());
    ui->webView->setMaximumSize(ui->scrollArea->maximumSize());
    ui->webView->setSizePolicy(ui->scrollArea->sizePolicy());

    ui->action_Tout_r_duire->setShortcut(QKeySequence("Ctrl+W"));
    ui->action_Exporter->setShortcut(QKeySequence("Ctrl+S"));
    ui->actionMettre_jour->setShortcut(QKeySequence("F5"));
    ui->action_Plein_cran->setShortcut(QKeySequence("F11"));
    ui->action_Quitter->setShortcut(QKeySequence("Ctrl+Q"));
    ui->actionParam_tres->setShortcut(QKeySequence(QKeySequence::Preferences));

    progressBar = new QProgressBar(this);
    statusBar()->addPermanentWidget(progressBar);
    pageLabel = new QLabel(this);
    statusBar()->addPermanentWidget(pageLabel);
    progressBar->setVisible(false);

    timer.setInterval(100);
    timer.setSingleShot(true);

    connect(&timer, SIGNAL(timeout()), this, SLOT(refreshDocument()));
    connect(ui->action_Tout_r_duire, SIGNAL(triggered()), this, SLOT(collapseAll()));
    connect(ui->actionMettre_jour, SIGNAL(triggered()), this, SLOT(updateXml()));
    connect(ui->action_Suivant, SIGNAL(triggered()), this, SLOT(nextDocument()));
    connect(ui->action_Pr_c_dant, SIGNAL(triggered()), this, SLOT(previousDocument()));
    connect(ui->actionPage_p_r_c_dante, SIGNAL(triggered()), this, SLOT(nextPage()));
    connect(ui->actionPage_suiva_nte, SIGNAL(triggered()), this, SLOT(previousPage()));
    connect(ui->action_Plein_cran, SIGNAL(triggered()), this, SLOT(fullscreen()));
    connect(ui->actionT_l_charger_tout_les_documents, SIGNAL(triggered()), this, SLOT(downloadAll()));
    connect(ui->action_Quitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->action_Exporter, SIGNAL(triggered()), this, SLOT(exportPdf()));
    connect(ui->actionModifier_les_sources, SIGNAL(triggered()), this, SLOT(changeSources()));
    connect(ui->actionParam_tres, SIGNAL(triggered()), this, SLOT(parameters()));
    connect(ui->treeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelected()));
    connect(&qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(documentDownloaded(QNetworkReply*)));

    if (!set.contains("urlList")) {
        set.setValue("urlList", "http://cmspc46.epfl.ch/20112012Data/Exercices/20112012semesters.xml");
    }

    QStringList list;
    list = set.value("nextDocumentKeys").toStringList();
    for (int i = 0; i < list.size(); ++i)
        nextDocumentKeys.append(QKeySequence(list[i]));
    list = set.value("previousDocumentKeys").toStringList();
    for (int i = 0; i < list.size(); ++i)
        previousDocumentKeys.append(QKeySequence(list[i]));
    list = set.value("nextPageKeys").toStringList();
    for (int i = 0; i < list.size(); ++i)
        nextPageKeys.append(QKeySequence(list[i]));
    list = set.value("previousPageKeys").toStringList();
    for (int i = 0; i < list.size(); ++i)
        previousPageKeys.append(QKeySequence(list[i]));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateXml(const QStringList &urls)
{
    if (!urls.isEmpty() || downloadLinks.isEmpty()) {
        if (urls.isEmpty())
            //downloadLinks << "http://cmspc46.epfl.ch/20112012Data/Exercices/20112012semesters.xml" << "http://setup.weeb.ch/qflex/data/index.xml";
            downloadLinks = set.value("urlList").toString().split(" ");
        else
            downloadLinks = urls;

        ui->treeWidget->clear();
        urlList.clear();
    }

    while (!replys.isEmpty())
        replys.takeLast()->abort();

    disconnect(&qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(documentDownloaded(QNetworkReply*)));
    connect(&qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(xmlFileDownloaded(QNetworkReply*)));

    if (downloadLinks.isEmpty())
        return;

    replys << qnam.get(QNetworkRequest(QUrl(downloadLinks.takeFirst())));

    statusBar()->showMessage(QString::fromUtf8("Téléchargement du fichier xml"));
}

void MainWindow::xmlFileDownloaded(QNetworkReply *reply)
{
    disconnect(&qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(xmlFileDownloaded(QNetworkReply*)));
    connect(&qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(documentDownloaded(QNetworkReply*)));

    QString key = urlToKey(reply->url().toString());
    QString urlPrefix = reply->url().toString().section('/', 0, -2);
    QByteArray data;

    if (reply->error() != QNetworkReply::NoError) {
        if (set.contains(key)) {
            data = set.value(key).toByteArray();
            readXmlFile(data, urlPrefix);
            statusBar()->showMessage(QString::fromUtf8("Pas de connexion au réseau. Récuperation du fichier xml locale"), 4000);
        } else {
            QMessageBox::warning(this, QString::fromUtf8("Erreur de réseau"), QString::fromUtf8("Erreur de téléchagement %1").arg(reply->errorString()));
        }
    } else {
        data = reply->readAll();
        readXmlFile(data, urlPrefix);
        set.setValue(key, data);
        statusBar()->showMessage(QString::fromUtf8("Fichier xml téléchargé"), 4000);
    }

    if (!downloadLinks.isEmpty()) {
        updateXml();
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

void MainWindow::readXmlFile(const QByteArray &data, const QString &urlPrefix)
{
    serverPrefix = urlPrefix;
    if (!serverPrefix.endsWith('/'))
        serverPrefix.append('/');

    xml.clear();
    xml.addData(data);

    if (xml.readNextStartElement()) {
        if (xml.name() == "semesters" || xml.name() == "others") {
            while (xml.readNextStartElement()) {
                if (xml.name() == "semesterentry" || xml.name() == "other") {
                    readXmlBlock(0);
                }
            }
        }
        ui->treeWidget->setItemExpanded(lastSemester, true);
        ui->treeWidget->setCurrentItem(lastSemester);
    }
    statusBar()->showMessage(QString::fromUtf8("Fichier xml déchifré"), 4000);
}

void MainWindow::readXmlBlock(QTreeWidgetItem *item)
{
    QTreeWidgetItem *branch = createChildItem(item);

    if (xml.name() == "semesterentry") {
        lastSemester = branch;
    }

    QString branchName;
    QUrl branchAddress;
    QString branchType;

    // Quand il tombe sur une balise fermée, readNextStartElement retourne false
    while (xml.readNextStartElement()) {

        if (xml.name() == "name") {
            // Si on tombe sur la balise name on lit son contenu, dufait, on se retrouve sur </name>
            branchName = xml.readElementText();
        } else if (xml.name() == "address") {
            // Idem que <name>
            branchAddress = serverPrefix + xml.readElementText();
        } else if (xml.name() == "type") {
            // O récupère l'attribut de la balise type, puis on saute </skip>
            branchType = xml.attributes().value("name").toString();
            xml.skipCurrentElement();
        } else {
            // Si c'est une autre balise, on relance récusivement la méthode
            readXmlBlock(branch);
        }
    }

    branch->setText(0, branchName);
    if (!branchType.isEmpty() && branchType != "null") {
        branch->setData(0, Qt::UserRole + 1, branchAddress);
        branch->setData(0, Qt::UserRole + 2, branchType);
        urlList << branchAddress;
    }
}

void MainWindow::itemSelected()
{
    if (downloadingAll) {
        downloadingAll = false;
        progressBar->setVisible(false);
        QMessageBox *message = new QMessageBox(QMessageBox::Warning, QString::fromUtf8("Téléchagement abandonnée"),
                                               QString::fromUtf8("Le téléchargement de tout les fichiers a été interrompu !"),
                                               QMessageBox::Ok, this);
        message->show();
    }
    QTreeWidgetItem *item = ui->treeWidget->currentItem();

    ui->label->clear();

    documentType = None;
    startDownload(item);
}

void MainWindow::startDownload(QTreeWidgetItem *item)
{
    while (!replys.isEmpty())
        replys.takeLast()->abort();

    if (!item->data(0, Qt::UserRole + 2).isNull()) {
        QUrl url(item->data(0, Qt::UserRole + 1).toString());

        QString key = urlToKey(url.toString());
        if (set.contains(key)) {
            QByteArray data = set.value(key).toByteArray();
            statusBar()->showMessage(QString::fromUtf8("Document locale %1").arg(url.toString().section('/', -1)), 4000);
            loadDocument(data, url.toString());
        } else {
            replys << qnam.get(QNetworkRequest(url));
            statusBar()->showMessage(QString::fromUtf8("Téléchargement de %1...").arg(url.toString().section('/', -1)));
        }
    } else {
        statusBar()->clearMessage();
    }
}

void MainWindow::documentDownloaded(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        statusBar()->clearMessage();
        statusBar()->showMessage(QString::fromUtf8("Erreur de téléchargement : %1").arg(reply->errorString()), 4000);
        ui->label->clear();
        return;
    }

    QByteArray data = reply->readAll();
    QString url = reply->url().toString();

    set.setValue(urlToKey(url), data);

    statusBar()->showMessage(QString::fromUtf8("Document téléchargé %1").arg(url.section('/', -1)), 4000);

    if (!downloadingAll) {
        loadDocument(data, url);
    } else {
        statusBar()->showMessage(QString::fromUtf8("Document téléchangé %1 (%2 / %3)").arg(url.section('/', -1))
                                 .arg(++downloaded).arg(amountOfDownload), 4000);
        progressBar->setVisible(true);
        progressBar->setMaximum(amountOfDownload);
        progressBar->setValue(downloaded);
        if (downloaded == amountOfDownload) {
            downloadingAll = false;
            progressBar->setVisible(false);
        }
    }

}

void MainWindow::loadDocument(const QByteArray &data, const QString &url)
{
    QString extention = url.section('.', -1);

    if (extention.compare("pdf", Qt::CaseInsensitive) == 0) {
        currentPage = 0;
        documentData = data;
        documentType = Pdf;
    } else if (extention.compare("html", Qt::CaseInsensitive) == 0) {
        documentData = data;
        documentUrl = url;
        documentType = Html;
    } else {
        if (!documentImage.loadFromData(data, extention.toAscii().data())) {
            statusBar()->showMessage(QString::fromUtf8("Erreur d'affichage de %1").arg(url.section('/', -1)), 4000);
        }
        documentType = Other;
    }

    refreshDocument();
}

void MainWindow::refreshDocument()
{
    ui->label->clear();
    pageLabel->clear();

    if (documentType == None) {
        ui->webView->setVisible(false);
        ui->scrollArea->setVisible(true);
        return;
    }

    if (documentType == Pdf) {
        ui->webView->setVisible(false);
        ui->scrollArea->setVisible(true);

        Poppler::Document *doc = Poppler::Document::loadFromData(documentData);
        if (doc != 0) {
            doc->setRenderHint(Poppler::Document::TextAntialiasing);
            doc->setRenderHint(Poppler::Document::TextHinting);
            doc->setRenderHint(Poppler::Document::Antialiasing);

            double width = doc->page(currentPage)->pageSizeF().width();
            double height = doc->page(currentPage)->pageSizeF().height();
            pageCount = doc->numPages();

            if (pageCount > 1) {
                pageLabel->setText(QString::fromUtf8("page %1/%2").arg(currentPage + 1).arg(pageCount));
            }

            double ratioX = ((double)ui->scrollArea->width() - 22) / width;
            double ratioY = ((double)ui->scrollArea->height() - 22) / height;
            double ratio;
            if (ratioX < ratioY || ratioY < 1.3) {
                ratio = ratioX;
            } else {
                ratio = ratioY;
            }
            ratio *= 72.0;

            ui->webView->setVisible(false);
            ui->scrollArea->setVisible(true);

            documentImage = doc->page(currentPage)->renderToImage(ratio, ratio);
            QPixmap pixmap = QPixmap::fromImage(documentImage);

            ui->label->setPixmap(pixmap);
            delete doc;

            return;
        } else {
            statusBar()->showMessage(QString::fromUtf8("Erreur d'affichage du fichier pdf %1").arg(documentUrl.toString().section('/', -1)));
            return;
        }
    }

    if ((documentType == Pdf) || (documentType == Other)) {
        ui->webView->setVisible(false);
        ui->scrollArea->setVisible(true);

        QPixmap pixmap = QPixmap::fromImage(documentImage);

        ui->label->setPixmap(pixmap);
    }

    if (documentType == Html) {
        ui->webView->setVisible(true);
        ui->scrollArea->setVisible(false);

        ui->webView->load(documentUrl);
    }
}

void MainWindow::nextDocument()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if (item == 0)
        return;

    while (true) {
        if (item->childCount() != 0)
            item = item->child(0);
        else
            item = ui->treeWidget->itemBelow(item);

        if (item == 0)
            break;

        if (!item->data(0, Qt::UserRole + 2).isNull()) {
            ui->treeWidget->setCurrentItem(item);
            return;
        }
    }
}

void MainWindow::previousDocument()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if (item == 0)
        return;

    while (true) {
        QTreeWidgetItem *above = ui->treeWidget->itemAbove(item);
        if (above != 0 && item->parent() != above && above->childCount() != 0) {
            while (above->childCount() != 0) {
                above = above->child(above->childCount() - 1);
            }
            item = above;
        } else {
            item = above;
        }

        if (item == 0)
            break;

        if (!item->data(0, Qt::UserRole + 2).isNull()) {
            ui->treeWidget->setCurrentItem(item);
            return;
        }
    }
}

void MainWindow::nextPage()
{
    if (currentPage + 1 < pageCount) {
        currentPage++;
        refreshDocument();
    }
}

void MainWindow::previousPage()
{
    if (currentPage > 0) {
        currentPage--;
        refreshDocument();
    }
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    timer.start();
    QMainWindow::resizeEvent(e);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    QKeySequence key = QKeySequence(e->modifiers() | e->key());
    //qDebug() << key.toString();

    e->accept();

    if (nextDocumentKeys.contains(key)) {
        nextDocument();
    } else if (previousDocumentKeys.contains(key)) {
        previousDocument();
    } else if (nextPageKeys.contains(key)) {
        nextPage();
    } else if (previousPageKeys.contains(key)) {
        previousPage();
    } else {
        e->ignore();
    }

    QMainWindow::keyPressEvent(e);
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
    downloadingAll = true;
    amountOfDownload = 0;
    downloaded = 0;
    for (int i = 0; i < urlList.size(); ++i) {
        if (!urlList[i].isEmpty() && !set.contains(urlToKey(urlList[i].toString()))) {
            replys << qnam.get(QNetworkRequest(urlList[i]));
            amountOfDownload++;
        }
    }
    if (amountOfDownload == 0) {
        downloadingAll = false;
        QMessageBox::information(this, QString::fromUtf8("Tout téléchager"), QString::fromUtf8("Tout les documents sont déjà téléchargé !"));
    }
}

void MainWindow::collapseAll()
{
    ui->treeWidget->collapseAll();
    ui->treeWidget->setItemExpanded(lastSemester, true);
    ui->treeWidget->setCurrentItem(lastSemester);
}

void MainWindow::exportPdf()
{
    if (documentType != Pdf) {
        QMessageBox::warning(this, QString::fromUtf8("Type erreur"), QString::fromUtf8("Ce document n'est pas un pdf !"));
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, QString::fromUtf8("Sauver le pdf"), QSettings().value("lastpdfdir", QDir::homePath()).toString(), "*.pdf");

    if (!fileName.isEmpty()) {
        QSettings().setValue("lastpdfdir", fileName);
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            file.write(documentData);
            file.close();
        } else {
            QMessageBox::warning(this, QString::fromUtf8("Erreur de fichier"), QString::fromUtf8("Le document n'a pas pu être sauvé : %1").arg(file.errorString()));
        }
    }
}

void MainWindow::changeSources()
{
    bool ok;
    QString list = QInputDialog::getText(this, QString::fromUtf8("Sources"),
                                         QString::fromUtf8("Séparez les liens vers les fichiers xml par le caractère espace"),
                                         QLineEdit::Normal, set.value("urlList").toString(), &ok);

    if (ok) {
        set.setValue("urlList", list);
    }
}

void MainWindow::parameters()
{
    OptionDialog dialog(this);

    dialog.setNextDocument(nextDocumentKeys);
    dialog.setPreviousDocument(previousDocumentKeys);
    dialog.setNextPage(nextPageKeys);
    dialog.setPreviousPage(previousPageKeys);

    if (dialog.exec() == QDialog::Accepted) {
        nextDocumentKeys = dialog.nextDocument();
        previousDocumentKeys = dialog.previousDocument();
        nextPageKeys = dialog.nextPage();
        previousPageKeys = dialog.previousPage();

        QStringList list;

        for (int i = 0; i < nextDocumentKeys.size(); ++i)
            list.append(nextDocumentKeys[i].toString());
        set.setValue("nextDocumentKeys", list);

        list.clear();
        for (int i = 0; i < previousDocumentKeys.size(); ++i)
            list.append(previousDocumentKeys[i].toString());
        set.setValue("previousDocumentKeys", list);

        list.clear();
        for (int i = 0; i < nextPageKeys.size(); ++i)
            list.append(nextPageKeys[i].toString());
        set.setValue("nextPageKeys", list);

        list.clear();
        for (int i = 0; i < previousPageKeys.size(); ++i)
            list.append(previousPageKeys[i].toString());
        set.setValue("previousPageKeys", list);
    }
}

