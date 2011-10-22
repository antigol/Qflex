#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtXml>
#include <QtNetwork>
#include <QTreeWidget>
#include <QTimer>
#include <QSettings>
#include <QtWebKit>

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
    void updateXml();

private slots:
    void itemSelected();
    void xmlFileDownloaded(QNetworkReply*);
    void documentDownloaded(QNetworkReply*);
    void nextDocument();
    void previousDocument();
    void refreshDocument();
    void fullscreen();
    void downloadAll();
    void collapseAll();

private:
    void startDownload(QTreeWidgetItem *item);
    void loadDocument(const QByteArray &data, const QString &url);
    QString urlToKey(const QString &url) const;
    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent *);
    QTreeWidgetItem *createChildItem(QTreeWidgetItem *item);
    void readXmlFile(const QByteArray &data);
    void readXmlBlock(QTreeWidgetItem *item);

    Ui::MainWindow *ui;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QXmlStreamReader xml;
    QTreeWidgetItem *lastSemester;
    QImage documentImage;

    QByteArray documentData;
    QUrl documentUrl;

    QTimer timer;
    QSettings set;
    enum {
        None,
        Pdf,
        Html,
        Other
    } documentType;
//    bool showDocuments;

    QList<QUrl> urlList;
};

#endif // MAINWINDOW_H
