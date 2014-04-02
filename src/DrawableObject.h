/********************DrawableObject.h******************/
#ifndef DRAWABLEOBJECT
#define DRAWABLEOBJECT

#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class DrawableObject {

public:

	//Constructor with window as a reference
    DrawableObject(sf::RenderWindow &window);

	//Setter and getter for Size
	void setSize(sf::Vector2f size);
	sf::vector2f getSize();
	
	//Setter and getter for Position
	void setPosition(sf::Vector2f pos);
	sf::vector2f getPosition();

	//Load the image named 'textureName' to the sf::Texture texture
	void loadTexture(sf::String textureName);

	//Sets the sf::Texture on texture to the sf::Sprite sprite
	void setTextureToSprite();
	
	//Draw the 'sprite' at 'position' with the size 'size' on the 'window'
	void draw();
	
	//Draw the 'sprite' at 'position' with the size 'size' on the 'otherWindow'
	void draw(sf::RenderWindow &otherWindow);
	
private:

   sf::RenderWindow& window;
   sf::Vector2f windowSize;
   sf::Vector2f position;
   sf::Vector2f size;
   
   sf::Texture texture;
   sf::Sprite sprite;
   
};

#endif