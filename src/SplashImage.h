/********************************SplashImage.h***************************************/

#ifndef SPLASHIMAGE
#define SPLASHIMAGE

#include <vector>
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
 		//Draw with a window as parameter
		void draw(sf::RenderWindow &Wind);

	private:
	    sf::Font mFont;
		std::string str;
		sf::Text escriptura;
		sf::Vector2f textPosition;
		std::vector<sf::Text> textos;
		//s'ha de guardar un vector de posicions per cada text ^
};


#endif
