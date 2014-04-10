/**************DrawableObject.cc****************/
#include "DrawableObject.h"

//Constructor with window as a reference
DrawableObject::DrawableObject(sf::RenderWindow &window) : window(window){
	windowSize = window.getSize();
	position.x = position.y = 0;
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
	std::stringstream s;
	s << "res/pictures/" << textureName << ".png";
	if(! texture.loadFromFile(s.str())) {
		std::cerr <<"Not able to load png" << s.str() << std::endl;
	}
	else {
		s << "res/pictures/" << textureName << ".jpg";
		if(! texture.loadFromFile(s.str())) 
			std::cerr <<"Not able to load jpg either" << s.str() << std::endl;
	}
}

//Sets the sf::Texture on texture to the sf::Sprite sprite
void DrawableObject::setTextureToSprite(){
	//The true is for texture rect to be reseted to the size of the new texture
	sprite.setTexture(texture, true);
}

//Sets the Rectangle defined for the variables from sf::Texture texture to the sf::Sprite sprite
void DrawableObject::setTextureRectToSprite(sf::IntRect rect){
	sprite.setTextureRect(rect);
}

//Draw the 'sprite' at 'position' with the size 'size' on the 'window'
void DrawableObject::draw(){
	draw(window);
}

//Draw the 'sprite' at 'position' with the size 'size' on the 'otherWindow'
void DrawableObject::draw(sf::RenderWindow &Wind){
	sprite.setTexture(texture);
	sprite.setPosition(position.x, position.y);	
	window.draw(sprite);
}






