#-------------------------------------------------
#
# Project created by QtCreator 2017-05-12T13:01:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TalentedGM
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/talentdata.cpp \
    src/stringvaluepair.cpp \
    src/menumodule.cpp \
    src/npctemplate.cpp \
    src/controller.cpp \
    src/editornpccontroller.cpp \
    src/locationtemplate.cpp \
    src/editorloccontroller.cpp

HEADERS  += src/mainwindow.h \
    src/talentdata.h \
    src/stringvaluepair.h \
    src/menumodule.h \
    src/npctemplate.h \
    src/controller.h \
    src/editornpccontroller.h \
    src/locationtemplate.h \
    src/editorloccontroller.h

FORMS    += src/mainwindow.ui
