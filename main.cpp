#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("cms2011-2012");
    a.setApplicationName("qflex");

    MainWindow w;
    w.show();

    w.updateXml();

    return a.exec();
}
