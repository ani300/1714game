/******************************Player.h**********************************/
#ifndef PLAYER
#define PLAYER

#include "Utils.h"
#include "DrawableObject.h"

class Player : public DrawableObject {

	public:
		//Constructor
		Player(sf::RenderWindow &window);

		//Destructor
		~Player();

	private:

};


#endif