/******************************MovileObject.h**********************************/
#ifndef MOVILEOBJECT
#define MOVILEOBJECT

#include "Utils.h"
#include "SceneNode.hpp"

class MovileObject: public SceneNode {

	public:
        //void moveIt(directions dir, float Movement);
        sf::Vector2f getVel() const;
		void setVel(float vx, float vy);
        void setVel(sf::Vector2f velocity);
        void setDirToVel(directions dir, float quantatMoviment);
	
	private:
        sf::Vector2f mVel;
		virtual void updateCurrent(sf::Time dt);
};

#endif
