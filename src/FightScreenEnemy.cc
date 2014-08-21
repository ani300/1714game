/******************************FightScreenEnemy.cc**********************************/
#include "FightScreenEnemy.h"

//Constructor
FightScreenEnemy::FightScreenEnemy(const sf::Texture& texture)
: mSprite(texture) {
}

sf::Vector2f FightScreenEnemy::getSize(){
    return sf::Vector2f(mSprite.getTexture()->getSize().x * mSprite.getScale().x, mSprite.getTexture()->getSize().y * mSprite.getScale().y);
}

void FightScreenEnemy::updateCurrent(sf::Time dt) {

}

void FightScreenEnemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}

void FightScreenEnemy::setSize(sf::Vector2u desiredSize){
    float scalex, scaley;
    scalex = scaley = 0.0;
    scalex = float(desiredSize.x)/mSprite.getTexture()->getSize().x;
    scaley = float(desiredSize.y)/mSprite.getTexture()->getSize().y;
//    std::cout << scalex << " " << scaley << std::endl;
    setScale(scalex, scaley);
}
