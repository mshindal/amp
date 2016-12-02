TARGET = amp
TEMPLATE = app
SOURCES += main.cpp\
        mainwindow.cpp \
    song.cpp \
    musicmodel.cpp \
    album.cpp \
    nowplaying.cpp \
    scanner.cpp
HEADERS  += mainwindow.h \
    song.h \
    musicmodel.h \
    album.h \
    nowplaying.h \
    scanner.h
QT += core gui multimedia widgets
CONFIG += c++11 link_pkgconfig
PKGCONFIG += taglib
