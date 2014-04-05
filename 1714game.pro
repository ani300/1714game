TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/main.cc src/Logic.cc src/Joc.cc src/Graphic.cc src/SplashImage.cc src/Player.cc
 
HEADERS += src/Logic.h src/Joc.h src/Graphic.h src/SplashImage.h src/Player.h

LIBS += -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
