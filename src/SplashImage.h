/********************************SplashImage.h***************************************/

#ifndef SPLASHIMAGE
#define SPLASHIMAGE

#include "Utils.h"
#include "DrawableObject.h"

class SplashImage: public DrawableObject {

	public:
		//Constructor
		SplashImage(sf::RenderWindow &window);
		//Constructor with name of the image it want's to display
		SplashImage(sf::RenderWindow &window, std::string pictureName);
		//Destructor
		~SplashImage();
		//Dibuixar
 		void draw();

	private:
		std::string str;
		sf::Text sftext;
};


#endif