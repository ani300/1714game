# Makefile super op

COMP11 = -std=c++11 -gstabs+

all: main DrawableObject Graphic Joc Logic Player SplashImage link

main: main.cpp
	g++ $(COMP11) -c src/main.cc -o Debug/main.o
	
DrawableObject: src/DrawableObject.*
	g++ $(COMP11) -c src/DrawableObject.cc -o Debug/DrawableObject.o

Graphic: src/Graphic.*
	g++ $(COMP11) -c src/Graphic.cc -o Debug/Graphic.o

Joc: src/Joc.*
	g++ $(COMP11) -c src/Joc.cc -o Debug/Joc.o

Logic: src/Logic.*
	g++ $(COMP11) -c src/Logic.cc -o Debug/Logic.o

Player: src/Player.*
	g++ $(COMP11) -c src/Player.cc -o Debug/Player.o

SplashImage: src/SplashImage.*
	g++ $(COMP11) -c src/SplashImage.cc -o Debug/SplashImage.o

link:
	g++ -o Debug/joc *.o -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

exe:
	./Debug/joc

clean:
	rm Debug/*.o Debug/joc