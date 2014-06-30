/***********************Joc.h****************************/
#ifndef JOC
#define JOC

#include "Utils.h"
#include "Estat.h"
#include "Logic.h"
#include "Graphic.h"
#include "SplashImage.h"
#include "DrawableObject.h"

class Joc {

	public:
		Joc();
		~Joc();

		int play();

	private:
		
		void processEvents();
		void readNextState(int& skipLines);
		
    	Logic logic;
        Estat* estat;
        sf::RenderWindow window;
        sf::Vector2u windowSize;
	    sf::RenderTexture rTexture;
};


#endif
