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
		//Constructor with name of the image it want's to display
        SplashImage(sf::RenderWindow *gaemWindow, sf::RenderTexture *gaemTexture, std::string document);

        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);

	private:
        void click(mouseButtons mouseButton, sf::Vector2f mouseClick);

	    sf::Font mFont;
        std::string str;
		sf::Text escriptura;
		sf::Vector2f textPosition;
		std::vector<sf::Text> textos;
		sf::RectangleShape fletxaRect;
		std::vector<sf::Vector2f> positions;
        std::wstring utf8_to_utf16(const std::string& utf8);

};


#endif
