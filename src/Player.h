/******************************player.h**********************************/
#ifndef PLAYER
#define PLAYER

#include "Utils.h"
#include "MovileObject.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

class Player: public MovileObject {

    public:
        //Constructor
        Player(const sf::Texture& texture);

        sf::Vector2f getSize();
        void setSize(sf::Vector2u desiredSize);

        sf::Color getColor();
        void setColor(sf::Color color);
        void setPosition(float posX, float posY);

    private:
        virtual void updateCurrent(sf::Time dt);
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        
        sf::Sprite mSprite;
        sf::Clock spriteTimmer;
        sf::Vector2f spriteSize;
        sf::Vector2f spriteSource;
};

#endif
