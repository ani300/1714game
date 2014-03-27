/******************************Player.h**********************************/
#ifndef PLAYER
#define PLAYER


#include <SFML/Graphics.hpp>

class Player {

	public:
		//Constructor
		Player();

		//Destructor
		~Player();

	private:
		//VARIABLES OBJECTS
		sf::Sprite sprite;
		sf::Texture texture;

		//VARIABLES VECTOR2F
		sf::vector2f position;
		sf::vector2f spriteSize;

		

};


#endif