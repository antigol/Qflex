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

private slots:
    void update();
    void itemChanged();
    void replyFinished(QNetworkReply*);
    void nextDocument();
    void previousDocument();

private:
    QTreeWidgetItem *createChildItem(QTreeWidgetItem *item);
    void readSemesters();
    void readAll(QTreeWidgetItem *item);

    Ui::MainWindow *ui;

    QNetworkAccessManager qnam;
    QXmlStreamReader xml;
};

#endif // MAINWINDOW_H
