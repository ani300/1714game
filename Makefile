all: joc

joc: src/main.cc src/Joc.cc
	g++ -gstabs+ -o Debug/joc src/main.cc src/Joc.cc src/Logic.cc src/Graphic.cc src/SplashImage.cc -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

clean: 
	rm Debug/joc