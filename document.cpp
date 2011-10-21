#include "document.h"
#include <poppler-qt4.h>
#include <QImage>

Document::Document(QObject *parent) :
    QObject(parent)
{

}

QPixmap Document::display(const QSizeF &outputSize)
{
    if (data.isEmpty()) {
        return QPixmap();
    }

    QImage image;

    if (type == "pdf") {
        Poppler::Document *doc = Poppler::Document::loadFromData(data);
        doc->setRenderHint(Poppler::Document::TextAntialiasing);
        doc->setRenderHint(Poppler::Document::TextHinting);
        doc->setRenderHint(Poppler::Document::Antialiasing);

        if (!size.isValid()) {
            size.setWidth(doc->page(0)->pageSizeF().width());
            size.setHeight(doc->page(0)->pageSizeF().height());
        }

        double ratioX = size.width() / outputSize.width();
        double ratioY = size.height() / outputSize.height();
        double ratio2;

        if (ratioX < ratioY || ratioY < 1.3) {
            ratio2 = ratioX;
        } else {
            ratio2 = ratioY;
        }
        ratio2 *= 72.0;
        image = doc->page(0)->renderToImage(ratio2, ratio2);

    } else if (type=="html") {
    } else {
        image.loadFromData(data, type.toAscii().data());
    }
    QPixmap pixmap = QPixmap::fromImage(image);

    return pixmap;
}

void Document::privateDownloadFinished()
{
}
