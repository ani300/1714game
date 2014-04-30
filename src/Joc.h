/***********************Joc.h****************************/
#ifndef JOC
#define JOC

#include "Utils.h"
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
		
		void render();
		void processEvents();
		void update(sf::Time elapsedTime);
		void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
		void readNextState(int& skipLines);
		
    	Logic logic;
		directions dir;
		mouseButtons mouseBut;
		sf::Vector2f mouseClick;
	    sf::RenderWindow window;
	    sf::RenderTexture rTexture;
	    sf::Vector2u windowSize;
	    sf::CircleShape mPlayer;
	    sf::Vector2f escala;
		std::vector<DrawableObject*> drawableObjects;
};


#endif
