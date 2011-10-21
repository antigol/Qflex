#-------------------------------------------------
#
# Project created by QtCreator 2011-10-18T21:51:00
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += network
QT       += webkit

TARGET = qflex
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    document.cpp

HEADERS  += mainwindow.h \
    document.h

FORMS    += mainwindow.ui

INCLUDEPATH  += /usr/include/poppler/qt4

LIBS         += -L/usr/lib -lpoppler-qt4
