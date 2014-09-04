/******************************Box.cc**********************************/
#include "Box.h"

//Constructor
Box::Box(const sf::Texture& texture)
: mSprite(texture) {
    setColisionBoundsPos(getPosition());
    movile = true;
    text = "";
}

sf::Vector2f Box::getSize(){
    return sf::Vector2f(mSprite.getTexture()->getSize().x * getScale().x, mSprite.getTexture()->getSize().y * getScale().y);
}

void Box::updateCurrent(sf::Time dt) {
    
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

//    move(getVel());
    move(getVel() * dt.asSeconds());
    setVel(sf::Vector2f(0,0));
//    if(getWorldPosition().x < 0) setPosition(0, getPosition().y);
//    if(getWorldPosition().y > 1920 - getSize().y)
//        setPosition(getPosition().x, 1920 - getSize().y);
    setColisionBoundsPos(getPosition());
//    setColisionBoundsPos(getPosition());
}

void Box::setPosition(float posX, float posY){
    sf::Transformable::setPosition(posX,posY);
    setColisionBoundsPos(sf::Vector2f(posX,posY));
}

void Box::setPosition(const sf::Vector2f& position){
    sf::Transformable::setPosition(position);
    setColisionBoundsPos(position);
}


void Box::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}

void Box::setSize(sf::Vector2u desiredSize){
    float scalex, scaley;
    scalex = scaley = 0.0;
    scalex = float(desiredSize.x)/mSprite.getTexture()->getSize().x;
    scaley = float(desiredSize.y)/mSprite.getTexture()->getSize().y;
    std::cout << scalex << " " << scaley << std::endl;
    setScale(scalex, scaley);

    setColisionBoundsSize(desiredSize);
}

void Box::setColor(sf::Color color){
    mSprite.setColor(color);
}

sf::Color Box::getColor(){
    return mSprite.getColor();
}

sf::FloatRect Box::getColisionBounds(){
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

void Box::setMovility(bool mov){
    movile = mov;
}

bool Box::getMovility(){
    return movile;
}

void Box::setText(std::string t){
    text = t;
}

std::string Box::getText(){
    return text;
}
