#include "Estat.h"

Estat::Estat(sf::RenderWindow *gaemWindow, sf::RenderTexture *gaemTexture) :
    rWindow(gaemWindow), rTexture(gaemTexture) {
        dir = dir_none;
        rWindow = gaemWindow;
        rTexture = gaemTexture;
        mouseBut = mouse_none;
        windowSize = rWindow->getSize();
        mouseClick = sf::Vector2f(0.0, 0.0);
}

Estat::~Estat() {
    // Neteja la memòria
    for (uint i = 0; i < drawableObjects.size(); ++i) {
        delete drawableObjects[i];
    }
}

void Estat::render() {
    rTexture->clear();
    for(int i = 0; i < drawableObjects.size(); ++i){
        drawableObjects[i]->draw(*rTexture);
    }
    rTexture->display();
}

void Estat::paint() {
    // Now we start rendering to the window, clear it first
    rWindow->clear();
    // Draw the texture
    sf::Sprite sprite(rTexture->getTexture());
    // Llegeix mida de la finestra (x, y)
    windowSize = rWindow->getSize();
    sprite.setScale(1.0, 1.0);
    escala = sf::Vector2f(float(windowSize.x)/float(rTexture->getSize().x), float(windowSize.y)/float(rTexture->getSize().y));
    sprite.setScale(escala);

    rWindow->draw(sprite);
    // End the current frame and display its contents on screen
    rWindow->display();
}

void Estat::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    dir = dir_none;
    if(isPressed){
        if (isPressed && key == sf::Keyboard::W) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir = dir_up_left;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir = dir_up_right;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dir = dir_none;
            else dir = dir_up;
        }
        if (isPressed && key == sf::Keyboard::S) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir = dir_down_left;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir = dir_down_right;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dir = dir_none;
            else dir = dir_down;
        }
        if (isPressed && key == sf::Keyboard::A) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dir = dir_up_left;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dir = dir_down_left;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir = dir_none;
            else dir = dir_left;
        }
        if (isPressed && key == sf::Keyboard::D) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dir = dir_up_right;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dir = dir_down_right;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir = dir_none;
            else dir = dir_right;
        }
    }
}
