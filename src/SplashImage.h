/********************************SplashImage.h***************************************/

#ifndef SPLASHIMAGE
#define SPLASHIMAGE

#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class SplashImage {

	public:
		//Constructor
		SplashImage();

		//Constructor with name of the image it want's to display
		SplashImage(std::string pictureName);

		//Destructor
		~SplashImage();

		//Dibuixar
		void draw(sf::RenderWindow& window);

	private:

		sf::Sprite sprite;
		sf::Texture texture;

};


#endif