#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QTreeWidgetItem>
#include <QUrl>
#include <QDate>

class Document : public QTreeWidgetItem
{
public:
    explicit Document(QTreeWidget *parent, int type = Type);

protected:

private:
    QByteArray data;
    QString name;
    QUrl url;
    QString key;
    QSizeF size;
    QString arbo;
    QString type;
    QDate lastUp;
};

#endif // DOCUMENT_H
