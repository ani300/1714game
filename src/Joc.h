/***********************Joc.h****************************/
#ifndef JOC
#define JOC

#include "Logic.h"
#include "Graphic.h"
#include "SplashImage.h"
#include <SFML/Graphics.hpp>

class Joc {

	public:
		Joc();

		int play();

	private:

	    sf::RenderWindow window;
	    Graphic graphic;
    	Logic logic;
};


#endif
