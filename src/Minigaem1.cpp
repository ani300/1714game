#include "Minigaem1.h"


//Constructor
Minigaem1::Minigaem1() : window(sf::VideoMode::getDesktopMode(), L"1714: La resistència de l'Història"
//Joc::Joc() : window(sf::VideoMode(800,600), L"1714: La resistència de l'Història"
    , sf::Style::Close), rTexture() {
    dir = dir_none;
    if (!rTexture.create(1920, 1080)) cout << "OPMERDA: No pot crear la RenderTexture" << endl;
    rTexture.setSmooth(true);
}

Minigaem1::~Minigaem1() {
    // Neteja la memòria
    for (uint i = 0; i < drawableObjects.size(); ++i) {
        delete drawableObjects[i];
    }
}

void Minigaem1::processEvents() {
    sf::Event event;
    while(window.pollEvent(event)) {
        switch(event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code,true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code,false);
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) mouseBut = mouse_left;
                else if (event.mouseButton.button == sf::Mouse::Right) mouseBut = mouse_right;
                mouseClick.x = event.mouseButton.x;
                mouseClick.y = event.mouseButton.y;
                break;
            case sf::Event::Closed:
                window.close();
                break;
        }
    }
}

void Minigaem1::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {

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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dir = dir_up_left;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dir = dir_down_right;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir = dir_none;
            else dir = dir_right;
        }
    }


}

void Minigaem1::update(sf::Time elapsedTime) {
    for(int i = 0; i < drawableObjects.size(); ++i){

        if(dir != dir_none) { //THERE IS MOVEMENT
            sf::Vector2f movement(0.f,0.f);
            movement.x = dirx[dir] * elapsedTime.asSeconds();
            movement.y = diry[dir] * elapsedTime.asSeconds();
            drawableObjects[i]->move(movement);
            dir = dir_none;
        }
        if(mouseBut != mouse_none){
            drawableObjects[i]->click(mouseBut, mouseClick);
            mouseBut = mouse_none;
        }

    }
}

void Minigaem1::render() {
    rTexture.clear();
    for(int i = 0; i < drawableObjects.size(); ++i){
        drawableObjects[i]->draw(rTexture);
    }
    rTexture.display();

     // Now we start rendering to the window, clear it first
    window.clear();
    // Draw the texture
    sf::Sprite sprite(rTexture.getTexture());
    // Llegeix mida de la finestra (x, y)
    windowSize = window.getSize();
    sprite.setScale(1.0, 1.0);
    sf::Vector2f escala(float(windowSize.x)/float(rTexture.getSize().x), float(windowSize.y)/float(rTexture.getSize().y));
    sprite.setScale(escala);

    window.draw(sprite);
    // End the current frame and display its contents on screen
    window.display();
}

void Minigaem1::readNextState(int& skipLines){
    std::string doc;
    std::ifstream infile;
    infile.open("res/documents/Joc.txt");
    if(!infile.is_open()) std::cerr << "res/document/Joc.txt" << " no obert " << std::endl;

    for(int i = 0; i < skipLines; ++i) std::getline(infile,doc); // Saves the line in STRING.
    std::getline(infile,doc);
    //% means this line is a comment
    while(doc[0] == '%') {
        std::getline(infile,doc);
        ++skipLines;
    }

    switch(doc[0]){
        case 'S':
        {
            SplashImage* splashIm = new SplashImage(rTexture, doc);
            //buidar drawableObjects; -> IMPORTANTISSIM FER DELETE DELS PUNTERS!!!!!!!!!!!!!
            drawableObjects.push_back(splashIm);
            break;
        }
        case 'X':
            break;
        default:
            break;
    }
    infile.close();
}

int Minigaem1::play() {

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    int skipLines = 0;
    readNextState(skipLines);

    window.setVerticalSyncEnabled(true);

    while(window.isOpen()) {
//std::cerr << "game loop" << std::endl;
        std::ifstream estatFile;
        estatFile.open("res/documents/Status.txt");
        std::string stat;
        getline(estatFile, stat);
        estatFile.close();
        if(stat == "OK") {
            //delete OK from estatFile
            readNextState(skipLines);
        }
// std::cerr << "Estat comprobat" << std::endl;
// std::cerr << "I will processEvents" << std::endl;
        processEvents();
// std::cerr << "Events processed" << std::endl;
        timeSinceLastUpdate += clock.restart();

        while(timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
// std::cerr << "I will process events" << std::endl;
            processEvents();
// std::cerr << "event processed" << std::endl;
// std::cerr << "I will update" << std::endl;
            update(TimePerFrame);
// std::cerr << "update done" << std::endl;
        }
// std::cerr << "before render" << std::endl;
        render();
// std::cerr << "after render" << std::endl;
    }
    return EXIT_SUCCESS;
}
