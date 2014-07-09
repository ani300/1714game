/******************************MovileObject.h**********************************/
#ifndef MOVILEOBJECT
#define MOVILEOBJECT

#include "Utils.h"
#include "DrawableObject.h"

class MovileObject : public DrawableObject {

	public:
		//Constructor
        MovileObject(sf::RenderTexture &rTexture);
		//Destructor
        ~MovileObject();
        void move(directions dir, float Movement);
        void setDirToVel(directions dir, float quantatMoviment);
	private:

        sf::Vector2i vel;

};


#endif
