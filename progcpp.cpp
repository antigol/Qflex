#include <QtCore/QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>

QTextStream cout(stdout);
QTextStream cerr(stderr);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (a.arguments().size() < 2) {
        cerr << "Error arguments" << endl;
        return 1;
    }

    QFile file(a.arguments().at(1));

    if (!file.open(QIODevice::ReadOnly)) {
        cerr << "Error opening file : " << file.errorString() << endl;
        return 1;
    }

    QTextStream in(&file);

    cout << "# /bin/bash" << endl;

    while (!in.atEnd()) {
        QString line = in.readLine();

        line = line.section("<link>", 1).section("</link>", 0, 0);

        if (line.isEmpty())
            continue;

        cout << "wget " << line << endl;
    }

    file.close();

    return 0;
}
