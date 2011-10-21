#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>
#include <QUrl>
#include <QSizeF>
#include <QPixmap>
#include <QDate>
#include <QByteArray>

class Document : public QObject
{
    Q_OBJECT
public:
    explicit Document(QObject *parent = 0);

    QPixmap display(const QSizeF &outputSize);
    bool load();
    void startDownload();
    void save();

signals:
    void downloadFinished(bool error);

private slots:
    void privateDownloadFinished();

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
