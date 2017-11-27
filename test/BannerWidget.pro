QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BannerWidget
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ../BannerWidget.cpp

HEADERS += \
    mainwindow.h \
    ../BannerWidget.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += $$PWD/..
