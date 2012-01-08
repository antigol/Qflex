#-------------------------------------------------
#
# Project created by QtCreator 2011-10-18T21:51:00
#
#-------------------------------------------------

QT        += core gui
QT        += xml
QT        += network
QT        += webkit

TARGET     = qflex
TEMPLATE   = app


SOURCES   += main.cpp\
    mainwindow.cpp \
    document.cpp \
    keylineedit.cpp \
    optiondialog.cpp \
    tree.cpp

HEADERS   += mainwindow.h \
    document.h \
    keylineedit.h \
    optiondialog.h \
    tree.h

FORMS     += mainwindow.ui \
    optiondialog.ui


RESOURCES += \
    images.qrc

# chemin vers le dossier contenant le header : "poppler-qt4.h"
INCLUDEPATH  += /usr/include/poppler/qt4

# option pour le linkage de la libraire poppler
LIBS         += -L/usr/lib -lpoppler-qt4

unix {
    menu.files = Qflex.desktop
    menu.path = /usr/share/applications

    share.files = qflex.svg
    share.path = /usr/share/qflex

    target.path = /usr/local/bin
    INSTALLS += target menu share
}

mac {
    OTHER_FILES += \
        ../../../../../../opt/local/lib/libpoppler-qt4.3.dylib
}
