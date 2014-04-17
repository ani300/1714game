/*********************************SplashImage.cpp***********************************/
#include "SplashImage.h"

//Constructor
SplashImage::SplashImage(){

}

//Constructor with name of the image it want's to display
SplashImage::SplashImage(std::string document){
	std::stringstream s;
	s << "res/document/" << document;
	str = s.c_str();
}

//Destructor
SplashImage::~SplashImage(){

}

// void SplashImage::draw(sf::RenderWindow& window){
// 	window.draw(sprite);
// }