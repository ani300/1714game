/******************************Player.cc**********************************/
#include "Player.h"

//Constructor
Player::Player(sf::RenderTexture &rTexture): DrawableObject(rTexture) {
    vel.x = vel.y = 0;
}

//Destructor
Player::~Player() {
}

void Player::move(directions dir, float quantatMoviment){
    setDirToVel(dir, quantatMoviment);
    position.x += vel.x;
    position.y += vel.y;
    if(position.x < 0) position.x = 0;
    else if(position.x + this->getSize().x > gameSize.x) position.x = gameSize.x - this->getSize().x;
    if(position.y < 0) position.y = 0;
    else if(position.y + this->getSize().y > gameSize.y) position.y = gameSize.y - this->getSize().y;
    vel.x = vel.y = 0; 
}

void Player::setDirToVel(directions dir, float quantatMoviment){
    vel.x = dirx[dir] * quantatMoviment;
    vel.y = diry[dir] * quantatMoviment;
}
