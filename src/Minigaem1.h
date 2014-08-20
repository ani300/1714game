#ifndef MINIGAEM1_H
#define MINIGAEM1_H

#include "Utils.h"
#include "SplashImage.h"
#include "DrawableObject.h"


class Minigaem1 {

    public:
        Minigaem1();
        ~Minigaem1();

      //  int play();

    private:

//         void render();
//         void processEvents();
//         void update(sf::Time elapsedTime);
//         void readNextState(int& skipLines);
//         void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
//         //void move(sf::Vector2f &movement);

        
        directions dir;
        mouseButtons mouseBut;
        sf::Sprite mPlayer;
        sf::Texture tplayer;
        sf::Vector2f escala;
        sf::Sprite mBackground;
        sf::RenderWindow window;
        sf::Vector2u windowSize;
        sf::Vector2f mouseClick;
        sf::Texture tbackground;
        sf::RenderTexture rTexture;

        std::vector<DrawableObject*> drawableObjects;
};

#endif // MINIGAEM1_H
