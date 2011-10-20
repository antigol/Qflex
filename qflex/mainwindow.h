#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtXml>
#include <QtNetwork>
#include <QTreeWidget>

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
    void itemDoubleClick(QTreeWidgetItem*,int);
    void xmlFileDownloaded(QNetworkReply*);
    void documentDownloaded(QNetworkReply*);
    void nextDocument();
    void previousDocument();

private:
    QTreeWidgetItem *createChildItem(QTreeWidgetItem *item);
    void readXmlBlock(QTreeWidgetItem *item);

    Ui::MainWindow *ui;

    QNetworkAccessManager qnam;
    QXmlStreamReader xml;
    QImage image;
};

#endif // MAINWINDOW_H
