all: joc

joc: src/main.cc src/Joc.cc
	g++ -gstabs+ -o Debug/joc -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio src/main.cc src/Joc.cc  

clean: 
	rm Debug/joc