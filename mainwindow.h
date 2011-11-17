#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtXml>
#include <QtNetwork>
#include <QTreeWidget>
#include <QTimer>
#include <QSettings>
#include <QtWebKit>
#include <QProgressBar>
#include <QLabel>
#include <QKeySequence>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateXml(const QStringList &urls = QStringList());

private slots:
    void itemSelected();
    void xmlFileDownloaded(QNetworkReply*);
    void documentDownloaded(QNetworkReply*);
    void nextDocument();
    void previousDocument();
    void nextPage();
    void previousPage();
    void refreshDocument();
    void fullscreen();
    void downloadAll();
    void collapseAll();
    void exportPdf();
    void changeSources();
    void parameters();

private:
    void startDownload(QTreeWidgetItem *item);
    void loadDocument(const QByteArray &data, const QString &url);
    QString urlToKey(const QString &url) const;
    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent *);
    QTreeWidgetItem *createChildItem(QTreeWidgetItem *item);
    void readXmlFile(const QByteArray &data, const QString &urlPrefix);
    void readXmlBlock(QTreeWidgetItem *item);

    Ui::MainWindow *ui;
    QList<QLabel *> labels;
    QNetworkAccessManager qnam;
    QStringList downloadLinks;
    QString serverPrefix;

    QList<QNetworkReply *> replys;
    QXmlStreamReader xml;
    QTreeWidgetItem *lastSemester;
    QImage documentImage;

    QByteArray documentData;
    QUrl documentUrl;
    int currentPage;
    int pageCount;

    QTimer timer;
    QSettings set;
    enum {
        None,
        Pdf,
        Html,
        Other
    } documentType;

    bool downloadingAll;
    int downloaded;
    int amountOfDownload;
    QProgressBar *progressBar;
    QList<QUrl> urlList;

    QList<QKeySequence> nextDocumentKeys;
    QList<QKeySequence> previousDocumentKeys;
    QList<QKeySequence> nextPageKeys;
    QList<QKeySequence> previousPageKeys;
};

#endif // MAINWINDOW_H
