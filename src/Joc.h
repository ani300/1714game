/***********************Joc.h****************************/
#ifndef JOC
#define JOC

#include "Logic.h"
#include "Graphic.h"
#include "SplashImage.h"
#include <SFML/Graphics.hpp>

class Joc {
    
  public:
    Joc();
    
    int play();
    
  private:
    void render();
    void processEvents();
    void update(sf::Time elapsedTime);
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    Graphic graphic;
    Logic logic;
    sf::RenderWindow window;
    sf::CircleShape mPlayer;
    
    static const float PlayerSpeed;
    static const sf::Time TimePerFrame;
    
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;
};

#endif
