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
    player.setSize(sf::Vector2f (gameSize.x/10, gameSize.y/4));

    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    int boxQtty = atoi(tex.c_str());
    for(int b = 0; b < boxQtty; ++b){
        DrawableObject box(*gaemTexture);
        getline(infile, tex);
        while(tex[0] == '%') getline(infile, tex);
        box.loadTexture(tex);
        box.setTextureToSprite();
        box.setSize(sf::Vector2f (200, 200));
        box.setPosition(sf::Vector2f(960-100,540-100));
        boxes.push_back(box);
    }
    background.setSize(sf::Vector2f (gaemTexture->getSize()));
}

MinigaemFitIt::~MinigaemFitIt() {  
}

void MinigaemFitIt::update(sf::Time elapsedTime) {
    player.move(dir, 200*(elapsedTime.asSeconds()));
}

void MinigaemFitIt::handlePlayerMouse(mouseButtons mouseBut, sf::Vector2f mouseClick){
    //o no
}

void MinigaemFitIt::render(){
    drawableObjects.empty();
    drawableObjects.push_back(&background);
    drawableObjects.push_back(&player);
    for(int i = 0; i < boxes.size(); ++i){
        drawableObjects.push_back(&boxes[i]);
    }
    Estat::render();
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
        
        
