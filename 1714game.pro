TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS = -std=c++11

SOURCES += src/main.cc src/Logic.cc src/Joc.cc src/Graphic.cc src/SplashImage.cc src/Player.cc src/DrawableObject.cc
 
HEADERS += src/Logic.h src/Joc.h src/Graphic.h src/SplashImage.h src/Player.h \
    src/Utils.h src/DrawableObject.h

LIBS += -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
