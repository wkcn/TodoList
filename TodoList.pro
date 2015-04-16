#-------------------------------------------------
#
# Project created by QtCreator 2015-04-14T22:35:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TodoList
TEMPLATE = app


SOURCES += main.cpp\
    Defines.cpp \
    PA.cpp \
    TodoItem.cpp \
    TodoList.cpp

HEADERS  += \
    Defines.h \
    PA.h \
    TodoItem.h \
    TodoList.h

FORMS    += todolist.ui
