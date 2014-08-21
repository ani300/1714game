/******************************box.h**********************************/
#ifndef BOX
#define BOX

#include "Utils.h"
#include "MovileObject.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

class Box: public MovileObject {

    public:
        //Constructor
        Box(const sf::Texture& texture);

        sf::Vector2f getSize();
        void setSize(sf::Vector2u desiredSize);

        sf::Color getColor();
        void setColor(sf::Color color);
        sf::FloatRect getColisionBounds();
        void setPosition(float posX, float posY);
        void setPosition(const sf::Vector2f& position);
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void updateCurrent(sf::Time dt);
        
        sf::Sprite mSprite;
        sf::Clock spriteTimmer;
};

#endif // BOX
