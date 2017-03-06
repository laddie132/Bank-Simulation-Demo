#-------------------------------------------------
#
# Project created by QtCreator 2015-06-09T19:11:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bank2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    check.cpp \
    dialog.cpp \
    pause.cpp \
    pnumber.cpp \
    statices.cpp \
    work.cpp \
    configw.cpp \
    fileprint.cpp \
    vipinform.cpp \
    vipadd.cpp \
    vipdelete.cpp \
    vipupdate.cpp \
    staticesw.cpp

HEADERS  += mainwindow.h \
    bank.h \
    dialog.h \
    configw.h \
    vipinform.h \
    vipadd.h \
    vipdelete.h \
    vipupdate.h \
    staticesw.h

FORMS    += mainwindow.ui \
    dialog.ui \
    configw.ui \
    vipinform.ui \
    vipadd.ui \
    vipdelete.ui \
    vipupdate.ui \
    staticesw.ui

RESOURCES += \
    resouse.qrc

DISTFILES +=

RC_FILE = bank.rc