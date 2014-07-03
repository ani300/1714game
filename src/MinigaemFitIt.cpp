/******************************MinigaemFitIt.cpp**********************************/
#include "MinigaemFitIt.h"

//Constructor
MinigaemFitIt::MinigaemFitIt(sf::RenderWindow *gaemWindow, sf::RenderTexture *gaemTexture):  
    Estat(gaemWindow, gaemTexture), player(*gaemTexture), background(*gaemTexture){
        
    std::string tex;
    std::ifstream infile;
    infile.open ("res/documents/MinigaemFitIt.txt");
    if(!infile.is_open()) std::cerr << "No puc obrir el document del Minigaem Fit It" << std::endl;

    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    background.loadTexture(tex.c_str());
    background.setTextureToSprite();
    
    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    player.loadTexture(tex.c_str());
    player.setTextureToSprite();
    
    
    background.setSize(sf::Vector2f (gaemTexture->getSize()));
    
    drawableObjects.push_back(&background);
    drawableObjects.push_back(&player);
}

MinigaemFitIt::~MinigaemFitIt() {  
}

void MinigaemFitIt::update(sf::Time elapsedTime) {
    player.move(dir, 200*(elapsedTime.asSeconds()));    
}

void MinigaemFitIt::handlePlayerMouse(mouseButtons mouseBut, sf::Vector2f mouseClick){
    //o no
}



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
        
        