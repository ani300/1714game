#ifndef ESTAT_H
#define ESTAT_H

#include "Utils.h"
#include "DrawableObject.h"

class Estat {
    public:
        Estat(sf::RenderWindow *gaemWindow, sf::RenderTexture *gaemTexture);
        virtual ~Estat();
        virtual void render();
        virtual void paint();
        virtual void update(sf::Time elapsedTime) = 0;
        virtual void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
        virtual void handlePlayerMouse(mouseButtons mouseBut, sf::Vector2f mouseClick) = 0;
    protected:
        sf::RenderWindow* rWindow;
        sf::RenderTexture* rTexture;
        sf::Vector2u windowSize;

        sf::Vector2f escala;
        std::vector<DrawableObject*> drawableObjects;
        directions dir;
        mouseButtons mouseBut;
        sf::Vector2f mouseClick;
};
#endif // ESTAT_H
