/******************************MovileObject.h**********************************/
#ifndef MOVILEOBJECT
#define MOVILEOBJECT

#include "Utils.h"
#include "SceneNode.hpp"

class MovileObject: public SceneNode {

	public:
        //void moveIt(directions dir, float Movement);
        void setVel(sf::Vector2f velocity);
		void setVel(float vx, float vy);
        void setDirToVel(directions dir, float quantatMoviment);
        sf::Vector2f getVel() const;
	private:
		virtual void updateCurrent(sf::Time dt);
        sf::Vector2f mVel;
};

#endif
