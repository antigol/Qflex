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
    void on_actionMettre_jour_triggered();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void replyFinished(QNetworkReply*);

private:
    QTreeWidgetItem *createChildItem(QTreeWidgetItem *item);
    void readSemesters();
    void readSemesterentry(QTreeWidgetItem *item);
    void readLectureentry(QTreeWidgetItem *item);
    void readSeriesentry(QTreeWidgetItem *item);
    void readExercice(QTreeWidgetItem *item);
    void readMethod(QTreeWidgetItem *item);

    Ui::MainWindow *ui;

    QNetworkAccessManager qnam;
    QXmlStreamReader xml;
};

#endif // MAINWINDOW_H
