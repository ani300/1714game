/******************************FightScreenPlayer.cc**********************************/
#include "FightScreenPlayer.h"

//Constructor
FightScreenPlayer::FightScreenPlayer(const sf::Texture& texture)
: mSprite(texture) {
    spriteSize.x = texture.getSize().x;///4;
    spriteSize.y = texture.getSize().y;///8;
    spriteSource.x = spriteSource.y = 0;
}

sf::Vector2f FightScreenPlayer::getSize(){
    return sf::Vector2f(spriteSize.x * mSprite.getScale().x, spriteSize.y * mSprite.getScale().y);
}

void FightScreenPlayer::updateCurrent(sf::Time dt) {
    
}


void FightScreenPlayer::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}

void FightScreenPlayer::setSize(sf::Vector2u desiredSize){
    float scalex, scaley;
    scalex = scaley = 0.0;
    scalex = float(desiredSize.x)/mSprite.getTexture()->getSize().x;
    scaley = float(desiredSize.y)/mSprite.getTexture()->getSize().y;
    setScale(scalex, scaley);
}
