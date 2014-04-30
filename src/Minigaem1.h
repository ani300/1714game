#ifndef MINIGAEM1_H
#define MINIGAEM1_H

#include "Utils.h"
#include "Logic.h"
#include "Graphic.h"
#include "SplashImage.h"
#include "DrawableObject.h"


class Minigaem1 {

    public:
        Minigaem1();
        ~Minigaem1();

        int play();

    private:

        void render();
        void processEvents();
        void update(sf::Time elapsedTime);
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
        void readNextState(int& skipLines);

        Logic logic;
        directions dir;
        mouseButtons mouseBut;
        sf::Vector2f mouseClick;
        sf::RenderWindow window;
        sf::RenderTexture rTexture;
        sf::Vector2u windowSize;
        sf::Texture tbackground;
        sf::Texture tplayer;
        sf::Sprite mPlayer;
        sf::Sprite mBackground;
        std::vector<DrawableObject*> drawableObjects;
};

#endif // MINIGAEM1_H
