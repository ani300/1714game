/*********************************SplashImage.cpp***********************************/
#include "SplashImage.h"

//Constructor
SplashImage::SplashImage(){

}

//Constructor with name of the image it want's to display
SplashImage::SplashImage(std::string pictureName){
	std::stringstream s;
	s << "res/pictures/" << pictureName << ".png";
	if(! texture.loadFromFile(s.str()))
		std::cout <<"Not able to load " << s.str() << std::endl;
	//the true is for texture rect  to be reseted to the size of the new texture
	sprite.setTexture(texture, true);
}

//Destructor
SplashImage::~SplashImage(){

}

void SplashImage::draw(sf::RenderWindow& window){
	window.draw(sprite);
}