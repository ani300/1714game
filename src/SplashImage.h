/********************************SplashImage.h***************************************/

#ifndef SPLASHIMAGE
#define SPLASHIMAGE

#include <vector>
#include "Utils.h"
#include "Estat.h"
#include <stdexcept>
#include "DrawableObject.h"

class SplashImage: public Estat {

	public:
		//Constructor
        SplashImage(sf::RenderWindow *gaemWindow, sf::RenderTexture *gaemTexture);
		//Constructor with name of the image it want's to display
        SplashImage(sf::RenderWindow *gaemWindow, sf::RenderTexture *gaemTexture, std::string document);
		//Destructor
        ~SplashImage();
		//Dibuixar
 		void draw();
 		//Draw with a window as parameter
		void draw(sf::RenderTexture &rTexture);

		void click(mouseButtons mouseButton, sf::Vector2f mouseClick);

        void render();
        void update(sf::Time elapsedTime);
        void handlePlayerMouse(mouseButtons mouseBut, sf::Vector2f mouseClick);

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
