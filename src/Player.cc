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
    vel.x = vel.y = 0; 
}

void Player::setDirToVel(directions dir, float quantatMoviment){
    vel.x = dirx[dir] * quantatMoviment;
    vel.y = diry[dir] * quantatMoviment;
}