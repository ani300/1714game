/******************************FightScreenPlayer.h**********************************/
#ifndef FIGHTSCREENPLAYER
#define FIGHTSCREENPLAYER

#include "Utils.h"
#include "SceneNode.hpp"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

class FightScreenPlayer: public SceneNode {

    public:
        //Constructor
        FightScreenPlayer(const sf::Texture& texture);

        sf::Vector2f getSize();
        void setSize(sf::Vector2u desiredSize);

        void decreaseLifes();
        void getLifes();
    private:
        virtual void updateCurrent(sf::Time dt);
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        
        sf::Sprite mSprite;
        sf::Clock spriteTimmer;
        sf::Vector2f spriteSize;
        sf::Vector2f spriteSource;

        int mLives;
};

#endif //FIGHTSCREENPLAYER
