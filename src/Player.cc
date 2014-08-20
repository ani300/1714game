/******************************Player.cc**********************************/
#include "Player.h"

//Constructor
Player::Player(const sf::Texture& texture)
: mSprite(texture) {
    spriteSize.x = texture.getSize().x/4;
    spriteSize.y = texture.getSize().y/8;
    spriteSource.x = spriteSource.y = 0;
}

sf::Vector2f Player::getSize(){
    return sf::Vector2f(spriteSize.x * mSprite.getScale().x, spriteSize.y * mSprite.getScale().y);
}

void Player::updateCurrent(sf::Time dt) {
    
    // TODO: Posar tot això al handler de input
    /*if(spriteSource.y == dir){
        MovileObject::moveIt(dir, Movement);
        float aux = spriteTimmer.getElapsedTime().asSeconds();
        if(aux >= 0.091) {
            ++spriteSource.x;
            spriteTimmer.restart();
        }
    }
    else if(dir != dir_none) spriteSource.y = dir;

    if(spriteSource.x >= 4) spriteSource.x = 0;
    */
    move(getVel());
    mSprite.setTextureRect(sf::IntRect(spriteSource.x*spriteSize.x,
                                      spriteSource.y*spriteSize.y,
                                      spriteSize.x,  spriteSize.y ));
}


void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}

void Player::setSize(sf::Vector2u desiredSize){
    float scalex, scaley;
    scalex = scaley = 0.0;
    scalex = float(desiredSize.x)/mSprite.getTexture()->getSize().x;
    scaley = float(desiredSize.y)/mSprite.getTexture()->getSize().y;
    setScale(scalex, scaley);
}

void Player::setColor(sf::Color color){
    mSprite.setColor(color);
}

sf::Color Player::getColor(){
    return mSprite.getColor();
}
