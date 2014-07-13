/********************************SplashImage.h***************************************/

#ifndef SPLASHIMAGE
#define SPLASHIMAGE

#include "Utils.h"
#include "Estat.h"
#include "DrawableObject.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

class SplashImage: public Estat {

	public:
		//Constructor with name of the image it want's to display
        SplashImage(PilaEstats& stack, Context context);
        SplashImage(PilaEstats& stack, Context context, std::string document);

        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);

	private:
        void click(mouseButtons mouseButton, sf::Vector2f mouseClick);
        std::wstring utf8_to_utf16(const std::string& utf8);

        TextureHolder mOwnTextures;
        std::string str;
		sf::Text escriptura;
		sf::Vector2f textPosition;
		std::vector<sf::Text> textos;
		sf::RectangleShape fletxaRect;
		std::vector<sf::Vector2f> positions;


};


#endif
