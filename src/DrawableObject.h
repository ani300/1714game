/********************DrawableObject.h******************/
#ifndef DRAWABLEOBJECT
#define DRAWABLEOBJECT

#include <string>
#include <sstream>
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class DrawableObject {

public:

	//Constructor with window as a reference
    DrawableObject(sf::RenderWindow &window);
	
	//Setter and getter for Position
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();

	//Load the image named 'textureName' to the sf::Texture texture
	void loadTexture(std::string textureName);

	//Sets the sf::Texture on texture to the sf::Sprite sprite
	void setTextureToSprite();
	
	//Sets the Rectangle defined for the variables from sf::Texture texture to the sf::Sprite sprite
	void setTextureRectToSprite(sf::IntRect rect);
	
	//Draw the 'sprite' at 'position' with the size 'size' on the 'window' ('xxx' are the private variables)
	void draw();
	
	//Draw the 'sprite' at 'position' with the size 'size' on the window 'Wind'
	void draw(sf::RenderWindow &Wind);
	
private:

   sf::RenderWindow& window;
   sf::Vector2u windowSize;
   sf::Vector2f position;
   sf::Texture texture;
   sf::Sprite sprite;
   
};

#endif