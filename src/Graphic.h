/******************************Graphic.h**********************************/
#ifndef GRAPHIC
#define GRAPHIC

#include <SFML/Graphics.hpp>

class Graphic {

	public:
		//Constructor
		Graphic(sf::RenderWindow& gameWindow);

		//Destructor
		~Graphic();

	private:

		sf::RenderWindow &window;

};

#endif