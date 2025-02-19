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
    src/npctemplate.cpp \
    src/controller.cpp \
    src/editornpccontroller.cpp \
    src/editorloccontroller.cpp \
    src/svpmenumodule.cpp \
    src/menumodule.cpp \
    src/temploccontroller.cpp \
    src/tempnpccontroller.cpp \
    src/tempplayercontroller.cpp \
    src/loctemplate.cpp \
    src/svp.cpp \
    src/filecontroller.cpp \
    src/talentfile.cpp \
    src/generalcontroller.cpp \
    src/tempnotescontroller.cpp \
    src/turn.cpp \
    src/turncontroller.cpp \
    src/turnnotescontroller.cpp \
    src/turnloccontroller.cpp \
    src/location.cpp \
    src/npc.cpp \
    src/npcmenumodule.cpp \
    src/hitarea.cpp \
    src/initiativeact.cpp \
    src/initmodule.cpp \
    src/turninitcontroller.cpp \
    src/module.cpp \
    src/turninfocontroller.cpp \
    src/skill.cpp \
    src/skillmenumodule.cpp \
    src/maincontroller.cpp \
    src/hashcontroller.cpp

HEADERS  += src/mainwindow.h \
    src/talentdata.h \
    src/npctemplate.h \
    src/controller.h \
    src/editornpccontroller.h \
    src/editorloccontroller.h \
    src/svpmenumodule.h \
    src/menumodule.h \
    src/temploccontroller.h \
    src/tempnpccontroller.h \
    src/tempplayercontroller.h \
    src/loctemplate.h \
    src/svp.h \
    src/filecontroller.h \
    src/talentfile.h \
    src/generalcontroller.h \
    src/tempnotescontroller.h \
    src/turn.h \
    src/turncontroller.h \
    src/turnnotescontroller.h \
    src/turnloccontroller.h \
    src/location.h \
    src/npc.h \
    src/npcmenumodule.h \
    src/hitarea.h \
    src/initiativeact.h \
    src/initmodule.h \
    src/turninitcontroller.h \
    src/module.h \
    src/turninfocontroller.h \
    src/skill.h \
    src/skillmenumodule.h \
    src/maincontroller.h \
    src/hashcontroller.h

FORMS    += src/mainwindow.ui

RESOURCES += \
    res/default.qrc
