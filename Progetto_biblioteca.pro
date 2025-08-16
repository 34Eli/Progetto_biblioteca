QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/Model/book.cpp \
    Sources/Model/digitalproduct.cpp \
    Sources/Model/film.cpp \
    Sources/Model/library.cpp \
    Sources/Model/main.cpp \
    Sources/Model/mainwindow.cpp \
    Sources/Model/music.cpp \
    Sources/Model/photograph.cpp \
    Sources/Model/physicalproduct.cpp \
    Sources/Model/product.cpp \
    Sources/Model/videogame.cpp \
    Sources/Data/XML/xmlreader.cpp \
    Sources/Data/JSON/jsonreader.cpp \
    visitor.cpp

HEADERS += \
    Sources/Headers/book.h \
    Sources/Headers/digitalproduct.h \
    Sources/Headers/film.h \
    Sources/Headers/library.h \
    Sources/Headers/mainwindow.h \
    Sources/Headers/music.h \
    Sources/Headers/photograph.h \
    Sources/Headers/physicalproduct.h \
    Sources/Headers/product.h \
    Sources/Headers/videogame.h \
    Sources/Data/XML/xmlreader.h \
    Sources/Data/JSON/jsonreader.h \
    visitor.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
