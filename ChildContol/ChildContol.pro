#-------------------------------------------------
#
# Project created by QtCreator 2016-02-04T17:03:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChildContol
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp \
    AppSettings.cpp \
    WebSettings.cpp \
    SettingsWidget.cpp

HEADERS  += MainWindow.h \
    AppSettings.h \
    WebSettings.h \
    SettingsWidget.h \
    ../Service/Includes/Common.h \
    ../Service/Includes/DataDumper.h \
    ../Service/Includes/DataTypes.h \
    ../Service/Includes/Utils.h \
    SttLib.h \
    applocalizer.h

FORMS    += MainWindow.ui \
    AppSettings.ui \
    WebSettings.ui \
    SettingsWidget.ui

RESOURCES = resource.qrc


