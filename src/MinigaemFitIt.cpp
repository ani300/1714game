/******************************MinigaemFitIt.cpp**********************************/
#include "MinigaemFitIt.h"

//Constructor
MinigaemFitIt::MinigaemFitIt(sf::RenderWindow *gaemWindow, sf::RenderTexture *gaemTexture):  
    Estat(gaemWindow, gaemTexture), player(*gaemTexture), background(*gaemTexture){
        
    if(!font.loadFromFile("res/media/Sansation.otf")) std::cout << "not able to load font sansation.otf" << std::endl;
    text.setFont(font);
    text.setPosition(100 , 0);
    text.setScale(sf::Vector2f(2,2));

    good_bad.x = good_bad.y = 0;
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
        int ran = rand()%2;
        goodBoxes.push_back(ran);
        if(ran == 0) box.setColor(sf::Color(200,0,0,250));
        else box.setColor(sf::Color(0,200,0,250));
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
<<<<<<< HEAD
    //this->handlePlayerInput();
    text.setString("Be: " + std::to_string(good_bad.x) + " Malament: " + std::to_string(good_bad.y));
    player.move(dir, 300*(elapsedTime.asSeconds()));
    for(int i = 0; i < boxes.size(); ++i){
        if (player.colide(boxes[i])) {
            sf::Vector2f aux = boxes[i].getPosition();
            boxes[i].move(dir, 310*(elapsedTime.asSeconds()));
            for(int k = 0; k < boxes.size(); ++k){
                if(k != i){
                    if(boxes[i].colide(boxes[k])){
                        boxes[k].move(dir, 315*elapsedTime.asSeconds());
                    }
                }
            }
            if(boxes[i].getPosition() == aux) player.move(inverseDir(dir), 300*(elapsedTime.asSeconds()));
        }
    }
    if(player.getPosition().y < 100) player.setPosition(sf::Vector2f(player.getPosition().x, 100));
    //Check boxes are in the game
    for(int i = 0; i < boxes.size(); ++i) {
        if(boxes[i].getPosition().x == gameSize.x - boxes[i].getSize().x) {

            if(boxes[i].getColor() == (sf::Color(0,200,0,250))) ++good_bad.x;
            else ++good_bad.y;

            int posx = rand()%gameSize.x -210;
            int posy = rand()%(gameSize.y-100) -100;
            int ran = rand()%2;
            goodBoxes[i] = ran;
            if(ran == 0) boxes[i].setColor(sf::Color(200,0,0,250));
            else boxes[i].setColor(sf::Color(0,200,0,250));
            boxes[i].setPosition(sf::Vector2f(posx, posy));
            boxes[i].move(dir, 0);
        }
        if(boxes[i].getPosition().y <= 100 - boxes[i].getSize().y/2) {

            if(boxes[i].getColor() == (sf::Color(200,0,0,250))) ++good_bad.x;
            else ++good_bad.y;

            int posx = rand()%gameSize.x - 210;
            int posy = rand()%(gameSize.y-100) - 100;
            int ran = rand()%2;
            goodBoxes[i] = ran;
            if(ran == 0) boxes[i].setColor(sf::Color(200,0,0,250));
            else boxes[i].setColor(sf::Color(0,200,0,250));
            boxes[i].setPosition(sf::Vector2f(posx, posy));
            boxes[i].move(dir, 0);
        }
    }

    if(good_bad.x - good_bad.y >= 1){
        std::cout << "Penguin" << std::endl;
        std::ofstream outfile;
        outfile.open("res/documents/Status.txt");
        if(!outfile.is_open()) std::cerr << "res/documents/Status.txt" << " no obert " << std::endl;
        outfile << "OK" << std::endl;
        outfile.close();
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
    rTexture->draw(text);

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
        
        
