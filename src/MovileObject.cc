/******************************MovileObject.cc**********************************/
#include "MovileObject.h"

// El substitueix updateCurrent() 
/*void MovileObject::moveIt(directions dir, float quantatMoviment){
    setDirToVel(dir, quantatMoviment);
    position.x += vel.x;
    position.y += vel.y;
    if(position.x < 0) position.x = 0;
    else if(position.x + this->getSize().x > gameSize.x) position.x = gameSize.x - this->getSize().x;
    if(position.y < 0) position.y = 0;
    else if(position.y + this->getSize().y > gameSize.y) position.y = gameSize.y - this->getSize().y;
    vel.x = vel.y = 0; 
}*/

void MovileObject::setDirToVel(directions dir, float quantatMoviment){
    mVel.x = dirx[dir] * quantatMoviment;
    mVel.y = diry[dir] * quantatMoviment;
}

void MovileObject::setVel(sf::Vector2f velocity) {
    mVel = velocity;
}

void MovileObject::setVel(float vx, float vy) {
    mVel.x = vx;
    mVel.y = vy;
}

sf::Vector2f MovileObject::getVel() const {
    return mVel;
}

void MovileObject::updateCurrent(sf::Time dt) {
    move(mVel * dt.asSeconds());
}


