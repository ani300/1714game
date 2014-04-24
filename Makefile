all: joc

joc: src/main.cc src/Joc.cc
	g++ -std=c++11 -gstabs+ -o Debug/joc src/*.cc -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

clean:  
	rm Debug/joc
