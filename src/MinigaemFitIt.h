/******************************MinigaemFitIt.h**********************************/
#ifndef MFI
#define MFI

#include "Utils.h"
#include "Estat.h"
#include "DrawableObject.h"

class MinigaemFitIt: public Estat {

    public:
        //Constructor
        MinigaemFitIt(sf::RenderWindow *gaemWindow, sf::RenderTexture *gaemTexture);

        //Destructor
        ~MinigaemFitIt();

         void update(sf::Time elapsedTime);
         void handlePlayerMouse(mouseButtons mouseBut, sf::Vector2f mouseClick);

    private:

        DrawableObject player, background;
        
        
    //heredats de Estat
        /*
        sf::RenderWindow* rWindow;
        sf::RenderTexture* rTexture;
        sf::Vector2u windowSize;

        sf::Vector2f escala;
        std::vector<DrawableObject*> drawableObjects;
        directions dir;
        mouseButtons mouseBut;
        sf::Vector2f mouseClick;
        */
};

#endif