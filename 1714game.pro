TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/main.cc src/Logic.cc src/Joc.cc src/Graphic.cc src/SplashImage.cc

LIBS += -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
