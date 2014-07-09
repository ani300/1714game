/********************DrawableObject.h******************/
#ifndef DRAWABLEOBJECT
#define DRAWABLEOBJECT

#include "Utils.h"

class DrawableObject {

public:

	//Constructor with window as a reference
    DrawableObject(sf::RenderTexture &rTexture);
	
    //Destructor
    ~DrawableObject();

	//Setter and getter for Position
    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition();

	//Load the image named 'textureName' to the sf::Texture texture
	void loadTexture(std::string textureName);
    sf::Texture getTexture();


	//Sets the sf::Texture on texture to the sf::Sprite sprite
    virtual void setTextureToSprite();
	
	//Sets the scale defined by the Vector2f to to the sf::Sprite sprite
	void setScaleToSprite(sf::Vector2f scaleValues);
	
	//Sets the Rectangle defined for the variables from sf::Texture texture to the sf::Sprite sprite
	void setTextureRectToSprite(sf::IntRect rect);
	
    //SetSize to the sprite scaling it respect to the texture size;
    void setSize(sf::Vector2f desiredSize);

    bool colide(DrawableObject& box);

	//Draw the 'sprite' at 'position' with the size 'size' on the 'window' ('xxx' are the private variables)
	virtual void draw();

	//Draw the 'sprite' at 'position' with the size 'size' on the window 'Wind'
	virtual void draw(sf::RenderTexture &rTexture);
	
	//Move --it is empty if the son would like to move he can implement it
    virtual void move();
    virtual void move(directions dir);
    virtual void move(sf::Vector2f &movement);    
	
    virtual sf::Vector2f getSize();
	//Click --same as move
	virtual void click(mouseButtons mouseButton, sf::Vector2f mouseClick);
	
private:
  
protected:
    sf::Sprite sprite;
    sf::Texture texture;
	sf::Vector2f position;
    sf::Vector2u windowSize;
    sf::RenderTexture& rTexture;
};

#endif
