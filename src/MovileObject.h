/******************************MovileObject.h**********************************/
#ifndef MOVILEOBJECT
#define MOVILEOBJECT

#include "Utils.h"
#include "SceneNode.hpp"

class MovileObject: public SceneNode {

	public:
        //void moveIt(directions dir, float Movement);
        MovileObject();
        sf::Vector2f getVel() const;
		void setVel(float vx, float vy);
        sf::FloatRect getColisionBounds();
        void setVel(sf::Vector2f velocity);
        void setColisionBoundsPos(sf::Vector2f pos);
        void setColisionBoundsSize(sf::Vector2u size);
        void setDirToVel(directions dir, float quantatMoviment);

	private:
        sf::Vector2f mVel;
        sf::FloatRect colisionBounds;
		virtual void updateCurrent(sf::Time dt);

};

#endif
