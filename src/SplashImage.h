/********************************SplashImage.h***************************************/

#ifndef SPLASHIMAGE
#define SPLASHIMAGE

#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

class SplashImage {

	public:
		//Constructor
		SplashImage();

		//Constructor with name of the image it want's to display
		SplashImage(std::String pictureName);

		//Destructor
		~SplashImage();

	private:

		sf::Sprite sprite;
		sf::Texture texture;

};


#endif