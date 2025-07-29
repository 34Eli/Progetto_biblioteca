QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    book.cpp \
    digitalproduct.cpp \
    film.cpp \
    main.cpp \
    mainwindow.cpp \
    music.cpp \
    photograph.cpp \
    physicalproduct.cpp \
    product.cpp \
    videogame.cpp

HEADERS += \
    book.h \
    digitalproduct.h \
    film.h \
    library.h \
    mainwindow.h \
    music.h \
    photograph.h \
    physicalproduct.h \
    product.h \
    videogame.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    library.json
