/******************************Player.h**********************************/
#ifndef PLAYER
#define PLAYER

#include "Utils.h"
#include "DrawableObject.h"

class Player : public DrawableObject {

	public:
		//Constructor
		Player(sf::RenderTexture &rTexture);

		//Destructor
		~Player();

        void move(directions dir, float Movement );

        void setDirToVel(directions dir, float quantatMoviment);
	private:

        sf::Vector2i vel;
};


#endif