/******************************FightScreenEnemy.h**********************************/
#ifndef FIGHTSCREENENEMY
#define FIGHTSCREENENEMY

#include "Utils.h"
#include "MovileObject.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

class FightScreenEnemy: public MovileObject {

    public:
        //Constructor
        FightScreenEnemy(const sf::Texture& texture);

        sf::Vector2f getSize();
        void setSize(sf::Vector2u desiredSize);

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void updateCurrent(sf::Time dt);
        
        sf::Sprite mSprite;
        sf::Clock spriteTimmer;
};

#endif // FIGHTSCREENENEMY
