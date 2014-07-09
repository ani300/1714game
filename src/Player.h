/******************************player.h**********************************/
#ifndef PLAYER
#define PLAYER

#include "Utils.h"
#include "MovileObject.h"

class Player : public MovileObject {

	public:
		//Constructor
        Player(sf::RenderTexture &rTexture);
		//Destructor
        ~Player();

        sf::Vector2f getSize();
        void setTextureToSprite();
        void move(directions dir, float Movement);

	private:

        sf::Clock spriteTimmer;
        sf::Vector2f spriteSize;
        sf::Vector2f spriteSource;
};


#endif
