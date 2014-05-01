/******************************Map.h**********************************/
#ifndef MAP
#define MAP

#include "Utils.h"
#include "DrawableObject.h"

class Map : public DrawableObject {

	public:
		//Constructor
		Map(sf::RenderTexture &rTexture);

		//Destructor
		~Map();

	private:

};


#endif