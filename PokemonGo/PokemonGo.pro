QT += core
QT -= gui

TARGET = tests
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    mapa.cpp \
    coordenada.cpp \
    aed2/ConjAcotado.cpp \
    juego.cpp \
    Driver.cpp \
    tests.cpp

HEADERS += \
    Mapa.h \
    Coordenada.h \
    TiposJuego.h \
    aed2/TiposBasicos.h \
    aed2/Arreglo.h \
    aed2/Conj.h \
    aed2/ConjAcotado.h \
    aed2/Dicc.h \
    aed2/Vector.h \
    mini_test.h \
    aed2/Lista.h \
    Juego.h \
    DiccString.hpp \
    ColaPrior.hpp \
    Driver.h

DISTFILES += \
    PokemonGo.pro.user

