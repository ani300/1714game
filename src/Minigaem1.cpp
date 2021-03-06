/******************************Minigaem1.cpp**********************************/
#include "Minigaem1.h"

//Constructor
Minigaem1::Minigaem1(PilaEstats& stack, Context context)
: Estat(stack, context)
, mPlayer(nullptr)
, mText(nullptr)
, mGood_bad(0, 0) {

}

Minigaem1::Minigaem1(PilaEstats& stack, Context context, std::string document)
: Estat(stack, context)
, mPlayer(nullptr)
, mText(nullptr)
, mGood_bad(0, 0){

    std::string tex;
    std::ifstream infile;

    std::stringstream s;
    s << "res/documents/" << document;
    std::cerr << s.str() << std::endl;
    infile.open (s.str());
    if(!infile.is_open()) std::cerr << "No puc obrir el document del Minigaem1" << std::endl;
        
    // CARREGA TEXTURES

    //Textura fons
    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    mOwnTextures.load(Textures::MG1Fons, Utils::getTexturePath(tex));
    
    //Textura player
    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    mOwnTextures.load(Textures::MG1Player, Utils::getTexturePath(tex));
    
    // CREACIÓ ESCENA
    // Inicialitza les dues capes
    for (std::size_t i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    // Prepara el fons de pantalla i la font
    sf::Texture& backTexture = mOwnTextures.get(Textures::MG1Fons);
    sf::Texture& playerTexture = mOwnTextures.get(Textures::MG1Player);
    sf::Font& font = getContext().fonts->get(Fonts::Sansation);

    // Add the background sprite to the scene
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(backTexture));

    // Centrar la pantalla i escalar la imatge
    float esc = float(gameSize.x)/float(backTexture.getSize().x);
    backgroundSprite->setScale(sf::Vector2f(esc, esc));
    backgroundSprite->setPosition(sf::Vector2f(0.0f, (gameSize.y-backTexture.getSize().y*esc)/2));
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

    // Prepara el text
    std::unique_ptr<TextNode> textNode(new TextNode(font, ""));
    mText = textNode.get(); // Guarda una referència al TextNode
    mText->setPosition(100 , 0);
    mText->setScale(sf::Vector2f(2,2));
    mSceneLayers[Text]->attachChild(std::move(textNode));

    
    // Genera les caixes a partir del fitxer
    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    int boxQtty = atoi(tex.c_str());
    std::cout << boxQtty << std::endl;

    for(int b = 0; b < boxQtty; ++b) {
        // Carrega la textura de la caixa
        mBoxTextures.load(b,Utils::getTexturePath("squareSusio"));
/*      getline(infile,tex);
        while(tex[0] == '%') getline(infile,tex);
        mBoxTextures.load(b,Utils::getTexturePath(tex));
*/
        // Crea la caixa
        std::unique_ptr<Box> boxNode(new Box(mBoxTextures.get(b)));
        mBoxes.push_back(boxNode.get());
        //mBoxes[b]->setSize(sf::Vector2u(200, 200));

        // Posició de la caixa
        int posx;
        int posy;
        if(b != 0) {
            posx = b*100;        
            posy = 100;
        }
        else {
            posx = 000;
            posy = 100;
        }
        mBoxes[b]->setPosition(sf::Vector2f(posx,posy));
        mBoxes[b]->setSize(sf::Vector2u(100, 100));

        // Decideix si és good box o no
        /*int ran = rand()%3;*/
        
        mGoodSquares.push_back(b);
        //if(b == 0) mBoxes[b]->setColor(sf::Color(200,0,0,250));

        // posa-la a la llista de coses a pintar
        mSceneLayers[Boxes]->attachChild(std::move(boxNode));
        //if(mPlayer->getColisionBounds().intersects(mBoxes[b]->getColisionBounds())) std::cerr << "HUEHUE" << std::endl;
    }
    // Prepara el jugador
    std::unique_ptr<Player> playerNode(new Player(playerTexture));
    mPlayer = playerNode.get();
    mPlayer->setSize(sf::Vector2u(100*4, 200*8));
    mSceneLayers[Boxes]->attachChild(std::move(playerNode));

}

/*
directions inverseDir(directions dir){
    if(dir == dir_none) return dir_none;
    if(dir%2 == 0) return static_cast<directions>(dir+1);
    else return static_cast<directions> (dir-1);
}

void Minigaem1::update(sf::Time elapsedTime) {

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

void Minigaem1::handlePlayerMouse(mouseButtons mouseBut, sf::Vector2f mouseClick){
    //o no
}
*/

void Minigaem1::draw() {
    // Print texts
    getContext().rTexture->draw(mSceneGraph);
}

bool Minigaem1::update(sf::Time dt) {
    handleRealtimeInput();
    mSceneGraph.update(dt);
    return true;
}

void Minigaem1::handleRealtimeInput(){

    bool moving = false;
    mPlayer->setVel(0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up   ) ) {
        mPlayer->setVel(mPlayer->getVel().x,mPlayer->getVel().y-5); moving = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down ) ) {
        mPlayer->setVel(mPlayer->getVel().x,mPlayer->getVel().y+5); moving = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left ) ) {
        mPlayer->setVel(mPlayer->getVel().x-5,mPlayer->getVel().y); moving = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ) {
        mPlayer->setVel(mPlayer->getVel().x+5,mPlayer->getVel().y); moving = true;
    }
    if(! moving) mPlayer->setVel(0,0);

}

bool Minigaem1::handleEvent(const sf::Event& event) {

    // Game input handling
    //CommandQueue& commands = mWorld.getCommandQueue();
    //mPlayer.handleEvent(event, commands);

    // Escape pressed, trigger the pause screen
    //if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    //    requestStackPush(States::Pause);

    return true;
}
