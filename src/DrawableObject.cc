/**************DrawableObject.cc****************/
#include "DrawableObject.h"

//Constructor with window as a reference
DrawableObject::DrawableObject(sf::RenderTexture &rTexture) : rTexture(rTexture) {
	position.x = position.y = 0;
} 

//Destructor
DrawableObject::~DrawableObject(){

}

void DrawableObject::setColor(sf::Color color){
    sprite.setColor(color);
}

sf::Color DrawableObject::getColor(){
    return sprite.getColor();
}

//Setter and getter for Position
void DrawableObject::setPosition(sf::Vector2f pos){
	position = pos;
}
sf::Vector2f DrawableObject::getPosition(){
	return position;
}

//Load the image named 'textureName' to the sf::Texture texture 
void DrawableObject::loadTexture(std::string textureName){
	std::stringstream png, jpg;
	png << "res/pictures/" << textureName << ".png";
	jpg << "res/pictures/" << textureName << ".jpg";
    if(texture.loadFromFile(png.str())){}
    else{
        std::cerr <<"Not able to load png i will try with jpg" << png.str() << std::endl;
        if(! texture.loadFromFile(jpg.str())) std::cerr <<"Not able to load " << jpg.str() <<  " either, it is a shiet "  << std::endl;
    }
}

sf::Texture DrawableObject::getTexture() {
    return texture;
}

//Sets the sf::Texture on texture to the sf::Sprite sprite
void DrawableObject::setTextureToSprite(){
	//The true is for texture rect to be reseted to the size of the new texture
	sprite.setTexture(texture, true);
}

void DrawableObject::setScaleToSprite(sf::Vector2f scaleValues){
	sprite.setScale(scaleValues);
}

//Sets the Rectangle defined for the variables from sf::Texture texture to the sf::Sprite sprite
void DrawableObject::setTextureRectToSprite(sf::IntRect rect){
	sprite.setTextureRect(rect);
}

//Draw the 'sprite' at 'position' with the size 'size' on the 'window'
void DrawableObject::draw(){
	draw(rTexture);
}

//Draw the 'sprite' at 'position' with the size 'size' on the 'otherWindow'
void DrawableObject::draw(sf::RenderTexture &rTexture){
	sprite.setTexture(texture);
	sprite.setPosition(position.x, position.y);	
	rTexture.draw(sprite);
}

void DrawableObject::move(){}
void DrawableObject::move(directions dir){}
void DrawableObject::move(sf::Vector2f &movement){
	//Do nothing... (whoever wants to be able to move should override this method)
}

void DrawableObject::click(mouseButtons mouseButton, sf::Vector2f mouseClick){
	//Do nothing also have to be overrided.
}

void DrawableObject::setSize(sf::Vector2f desiredSize){
    float scalex, scaley;
    scalex = scaley = 0.0;
    scalex = desiredSize.x/texture.getSize().x;
    scaley = desiredSize.y/texture.getSize().y;
    sprite.setScale(scalex, scaley);
}

sf::Vector2f DrawableObject::getSize(){
    float x, y;
    x = sprite.getTexture()->getSize().x * sprite.getScale().x;
    y = sprite.getTexture()->getSize().y * sprite.getScale().y;
    return sf::Vector2f(x,y);
}

bool DrawableObject::colide(DrawableObject& box){

    float left1, right1, top1, bot1;
    left1 = this->getPosition().x; right1 = left1 + this->getSize().x;
    top1 = this->getPosition().y; bot1 = top1 + this->getSize().y;

    float left2, right2, top2, bot2;
    left2 = box.getPosition().x; right2 = left2 + box.getSize().x;
    top2 = box.getPosition().y; bot2 = top2 + box.getSize().y;

    if(left1 > right2 || right1 < left2 ||
            top1 > bot2 || bot1 < top2  ) return false;
    else return true;

}
