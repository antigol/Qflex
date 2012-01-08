/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Fri Jan 6 15:51:15 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   12,   11,   11, 0x0a,
      40,   11,   11,   11, 0x2a,
      52,   11,   11,   11, 0x08,
      67,   11,   11,   11, 0x08,
     101,   11,   11,   11, 0x08,
     136,   11,   11,   11, 0x08,
     151,   11,   11,   11, 0x08,
     170,   11,   11,   11, 0x08,
     181,   11,   11,   11, 0x08,
     196,   11,   11,   11, 0x08,
     214,   11,   11,   11, 0x08,
     227,   11,   11,   11, 0x08,
     241,   11,   11,   11, 0x08,
     255,   11,   11,   11, 0x08,
     267,   11,   11,   11, 0x08,
     283,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0urls\0updateXml(QStringList)\0"
    "updateXml()\0itemSelected()\0"
    "xmlFileDownloaded(QNetworkReply*)\0"
    "documentDownloaded(QNetworkReply*)\0"
    "nextDocument()\0previousDocument()\0"
    "nextPage()\0previousPage()\0refreshDocument()\0"
    "fullscreen()\0downloadAll()\0collapseAll()\0"
    "exportPdf()\0changeSources()\0parameters()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateXml((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 1: updateXml(); break;
        case 2: itemSelected(); break;
        case 3: xmlFileDownloaded((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: documentDownloaded((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 5: nextDocument(); break;
        case 6: previousDocument(); break;
        case 7: nextPage(); break;
        case 8: previousPage(); break;
        case 9: refreshDocument(); break;
        case 10: fullscreen(); break;
        case 11: downloadAll(); break;
        case 12: collapseAll(); break;
        case 13: exportPdf(); break;
        case 14: changeSources(); break;
        case 15: parameters(); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
