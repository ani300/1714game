/******************************Player.cc**********************************/
#include "Player.h"

//Constructor
Player::Player(sf::RenderTexture &rTexture): MovileObject(rTexture) {

}

sf::Vector2f Player::getSize(){
    return sf::Vector2f(spriteSize.x * sprite.getScale().x, spriteSize.y * sprite.getScale().y);
}

void Player::move(directions dir, float Movement){
    if(spriteSource.y == dir){
        MovileObject::move(dir, Movement);
        float aux = spriteTimmer.getElapsedTime().asSeconds();
        if(aux >= 0.1) {
            ++spriteSource.x;
            spriteTimmer.restart();
        }
    }
    else if(dir != dir_none)spriteSource.y = dir;
    if(spriteSource.x >= 4) spriteSource.x = 0;
    sprite.setTextureRect(sf::IntRect(spriteSource.x*spriteSize.x,
                                      spriteSource.y*spriteSize.y,
                                      spriteSize.x,  spriteSize.y ));
}

void Player::setTextureToSprite(){
    DrawableObject::setTextureToSprite();
    spriteSize.x = texture.getSize().x/4;
    spriteSize.y = texture.getSize().y/8;
    spriteSource.x = spriteSource.y = 0;
}

//Destructor
Player::~Player() {
}


