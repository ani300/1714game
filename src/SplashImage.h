/********************************SplashImage.h***************************************/

#ifndef SPLASHIMAGE
#define SPLASHIMAGE

#include <vector>
#include "Utils.h"
#include <stdexcept>
#include "DrawableObject.h"

class SplashImage: public DrawableObject {

	public:
		//Constructor
		SplashImage(sf::RenderTexture &rTexture);
		//Constructor with name of the image it want's to display
        SplashImage(sf::RenderTexture &rTexture, std::string pictureName);
		//Destructor
		~SplashImage();
		//Dibuixar
 		void draw();
 		//Draw with a window as parameter
		void draw(sf::RenderTexture &rTexture);

		void click(mouseButtons mouseButton, sf::Vector2f mouseClick);

	private:
	    sf::Font mFont;
        std::string str;
		sf::Text escriptura;
		sf::Vector2f textPosition;
		std::vector<sf::Text> textos;
		std::vector<sf::Vector2f> positions;
		sf::RectangleShape fletxaRect;
        std::wstring utf8_to_utf16(const std::string& utf8);

};


#endif
