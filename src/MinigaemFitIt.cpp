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
    player.setSize(sf::Vector2f (100*4, 200*8));

    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    int boxQtty = atoi(tex.c_str());
    for(int b = 0; b < boxQtty; ++b){
        Player box(*gaemTexture);
        getline(infile, tex);
        while(tex[0] == '%') getline(infile, tex);
        box.loadTexture(tex);
        box.setTextureToSprite();
        box.setSize(sf::Vector2f (200, 200));
            getline(infile, tex);
            while(tex[0] == '%') getline(infile, tex);
        int posx = atoi(tex.c_str());
            getline(infile, tex);
            while(tex[0] == '%') getline(infile, tex);
        int posy = atoi(tex.c_str());
        box.setPosition(sf::Vector2f(posx,posy));
        boxes.push_back(box);
    }
    background.setSize(sf::Vector2f (gaemTexture->getSize()));

    drawableObjects.push_back(&background);
    drawableObjects.push_back(&player);
    for(int i = 0; i < boxes.size(); ++i){
        drawableObjects.push_back(&boxes[i]);
    }
}

MinigaemFitIt::~MinigaemFitIt() {
}

directions inverseDir(directions dir){
    if(dir == dir_none) return dir_none;
    if(dir%2 == 0) return static_cast<directions>(dir+1);
    else return static_cast<directions> (dir-1);
}

void MinigaemFitIt::update(sf::Time elapsedTime) {
    //this->handlePlayerInput();
    player.move(dir, 200*(elapsedTime.asSeconds()));
    for(int i = 0; i < boxes.size(); ++i){
        if (player.colide(boxes[i])) {
            sf::Vector2f aux = boxes[i].getPosition();
            boxes[i].move(dir, 200*(elapsedTime.asSeconds()));
            for(int k = 0; k < boxes.size(); ++k){
                if(k != i){
                    if(boxes[i].colide(boxes[k])){
                        boxes[k].move(dir, 200*elapsedTime.asSeconds());
                    }
                }
            }
            if(boxes[i].getPosition() == aux) player.move(inverseDir(dir), 200*(elapsedTime.asSeconds()));
        }
    }
    if(player.getPosition().y < 100) player.setPosition(sf::Vector2f(player.getPosition().x, 100));
    for(int i = 0; i < boxes.size(); ++i) {
        if(boxes[i].getPosition().x + boxes[i].getSize().x == gameSize.x) {
            //boxes.erase(boxes.begin()+i);
            boxes[i].setSize(sf::Vector2f(0,0));
            //drawableObjects.erase(drawableObjects.begin()+i+2);
        }
        if(boxes[i].getPosition().y <= 100 - boxes[i].getSize().y/2) {
            //boxes.erase(boxes.begin()+i);
            boxes[i].setSize(sf::Vector2f(0,0));
            //drawableObjects.erase(drawableObjects.begin()+i+2);
        }
    }
}

void MinigaemFitIt::handlePlayerMouse(mouseButtons mouseBut, sf::Vector2f mouseClick){
    //o no
}

void MinigaemFitIt::render(){
    /*drawableObjects.clear();
    drawableObjects.push_back(&background);
    drawableObjects.push_back(&player);
    for(int i = 0; i < boxes.size(); ++i){
        drawableObjects.push_back(&boxes[i]);
    }*/
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
        
        
