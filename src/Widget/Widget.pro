QT       += core gui opengl widgets openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#INCLUDEPATH+=../Widget/

SOURCES += \
    c_part/render.c \
    c_part/matrix.c \
    c_part/parser.c \
    main.cpp \
    mainwindow.cpp \
    glwidget.cpp


HEADERS += \
    c_part/render.h \
    c_part/matrix.h \
    c_part/parser.h \
    mainwindow.h \
    glwidget.h

include (../QtGifImage-master/src/gifimage/qtgifimage.pri)

FORMS += \
    mainwindow.ui \
    glwidget.ui

TRANSLATIONS += \
    ../Widget/Widget_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    ../QtGifImage-master/qtgifimage.pro

