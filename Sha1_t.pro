#-------------------------------------------------
#
# Project created by QtCreator 2021-01-28T09:54:34
#
#-------------------------------------------------

QT       -= core gui

TARGET = Sha1_t
TEMPLATE = lib

DEFINES += SHA1_T_LIBRARY

SOURCES += sha1_t.cpp

HEADERS += sha1_t.h\
        sha1_t_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
