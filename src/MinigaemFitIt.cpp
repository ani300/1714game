/******************************MinigaemFitIt.cpp**********************************/
#include "MinigaemFitIt.h"

//Constructor
MinigaemFitIt::MinigaemFitIt(PilaEstats& stack, Context context)
: Estat(stack, context)
, mPlayer(nullptr)
, mText(nullptr)
, mGood_bad(0, 0) {

}

MinigaemFitIt::MinigaemFitIt(PilaEstats& stack, Context context, std::string document)
: Estat(stack, context)
, mPlayer(nullptr)
, mText(nullptr)
, mGood_bad(0, 0)
{

    std::string tex;
    std::ifstream infile;

    std::stringstream s;
    s << "res/documents/" << document;
    std::cerr << s.str() << std::endl;
    infile.open (s.str());
    if(!infile.is_open()) std::cerr << "No puc obrir el document del Minigaem Fit It" << std::endl;
        
    // CARREGA TEXTURES

    //Textura fons
    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    mOwnTextures.load(Textures::MFIFons, Utils::getTexturePath(tex));
    
    //Textura player
    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    mOwnTextures.load(Textures::MFIPlayer, Utils::getTexturePath(tex));
    
    // CREACIÓ ESCENA
    // Inicialitza les dues capes
    for (std::size_t i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    // Prepara el fons de pantalla i la font
    sf::Texture& backTexture = mOwnTextures.get(Textures::MFIFons);
    sf::Texture& playerTexture = mOwnTextures.get(Textures::MFIPlayer);
    sf::Font& font = getContext().fonts->get(Fonts::Sansation);
    mText = new TextNode(font, "Penguin");
    mText->setPosition(0,0);

    // Add the background sprite to the scene
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(backTexture));

    //centrar la pantalla i escalar la imatge
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

    // Prepara el jugador
    std::unique_ptr<Player> playerNode(new Player(playerTexture));
    mPlayer = playerNode.get();
//    mPlayer->setSize(sf::Vector2u(100*4, 200*8));
    mPlayer->setSize(sf::Vector2u(100*4, 200*8));
    mSceneLayers[Boxes]->attachChild(std::move(playerNode));
    
    // Genera les caixes a partir del fitxer
    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    int boxQtty = atoi(tex.c_str());
    std::cout << boxQtty << std::endl;

    for(int b = 0; b < boxQtty; ++b) {
        // Carrega la textura de la caixa
        getline(infile, tex);
        while(tex[0] == '%') getline(infile, tex);
        mBoxTextures.load(b, Utils::getTexturePath(tex));

        // Crea la caixa
        std::unique_ptr<Box> boxNode(new Box(mBoxTextures.get(b)));
        mBoxes.push_back(boxNode.get());
        //mBoxes[b]->setSize(sf::Vector2u(200, 200));

        // Posició de la caixa
        getline(infile, tex);
        while(tex[0] == '%') getline(infile, tex);
        int posx = atoi(tex.c_str());
        getline(infile, tex);
        while(tex[0] == '%') getline(infile, tex);
        int posy = atoi(tex.c_str());
        mBoxes[b]->setPosition(sf::Vector2f(posx,posy));
        mBoxes[b]->setSize(sf::Vector2u(200, 200));

        // Decideix si és good box o no
        int ran = rand()%2;
        mGoodBoxes.push_back(ran);
        if(ran == 0) mBoxes[b]->setColor(sf::Color(200,0,0,250));
        else mBoxes[b]->setColor(sf::Color(0,200,0,250));

        // posa-la a la llista de coses a pintar
        mSceneLayers[Boxes]->attachChild(std::move(boxNode));
    }

}

/*
directions inverseDir(directions dir){
    if(dir == dir_none) return dir_none;
    if(dir%2 == 0) return static_cast<directions>(dir+1);
    else return static_cast<directions> (dir-1);
}

void MinigaemFitIt::update(sf::Time elapsedTime) {

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
*/

void MinigaemFitIt::draw() {
    // Print texts

    getContext().rTexture->draw(mSceneGraph);
}

bool MinigaemFitIt::update(sf::Time dt) {
    handleRealtimeInput();

    sf::Vector2f nextPlayerPosition;
    nextPlayerPosition.x = mPlayer->getPosition().x + mPlayer->getVel().x * dt.asSeconds();
    nextPlayerPosition.y = mPlayer->getPosition().y + mPlayer->getVel().y * dt.asSeconds();

    sf::FloatRect movedBoxRect;
    sf::FloatRect movedRect (nextPlayerPosition, mPlayer->getSize());

    if(movedRect.intersects(mBoxes[0]->getColisionBounds())){
        mPlayer->setVel(mPlayer->getVel().x/2,mPlayer->getVel().y/2);
        mBoxes[0]->setVel(1.0f * mPlayer->getVel());
        movedBoxRect = mBoxes[0]->getColisionBounds();
        movedBoxRect.left = mBoxes[0]->getPosition().x + mBoxes[0]->getVel().x * dt.asSeconds();
        movedBoxRect.top = mBoxes[0]->getPosition().y + mBoxes[0]->getVel().y * dt.asSeconds();
        if(movedBoxRect.intersects(mBoxes[1]->getColisionBounds()))
            mBoxes[1]->setVel(1.0f * mPlayer->getVel());
    }
    if(movedRect.intersects(mBoxes[1]->getColisionBounds())){
        mPlayer->setVel(mPlayer->getVel().x/2,mPlayer->getVel().y/2);
        mBoxes[1]->setVel(1.0f * mPlayer->getVel());
        movedBoxRect = mBoxes[1]->getColisionBounds();
        movedBoxRect.left = mBoxes[1]->getPosition().x + mBoxes[1]->getVel().x * dt.asSeconds();
        movedBoxRect.top = mBoxes[1]->getPosition().y + mBoxes[1]->getVel().y * dt.asSeconds();
        if(movedBoxRect.intersects(mBoxes[0]->getColisionBounds()))
            mBoxes[0]->setVel(1.0f * mPlayer->getVel());
    }

    mSceneGraph.update(dt);

    if(mPlayer->getPosition().y < 30) mPlayer->setPosition(mPlayer->getPosition().x, 30);
    if(mPlayer->getPosition().y > getContext().rTexture->getSize().y - mPlayer->getSize().y)
        mPlayer->setPosition(mPlayer->getPosition().x, getContext().rTexture->getSize().y - mPlayer->getSize().y);
    //Check boxes are in the game
    for(int i = 0; i < mBoxes.size(); ++i) {
        if(mBoxes[i]->getPosition().x >= gameSize.x - mBoxes[i]->getSize().x) {

            if(mBoxes[i]->getColor() == (sf::Color(0,200,0,250))) ++mGood_bad.x;
            else ++mGood_bad.y;

            do{
                int posx = rand()%(int)(gameSize.x -210 - mBoxes[i]->getSize().x) +mBoxes[i]->getSize().x;
                int posy = rand()%(int)(gameSize.y -100 - 2*mBoxes[i]->getSize().x) +mBoxes[i]->getSize().y +100;
                int ran = rand()%2;
                mGoodBoxes[i] = ran;
                if(ran == 0) mBoxes[i]->setColor(sf::Color(200,0,0,250));
                else mBoxes[i]->setColor(sf::Color(0,200,0,250));
                mBoxes[i]->setPosition(sf::Vector2f(posx, posy));
            }while(mBoxes[1]->getColisionBounds().intersects(mBoxes[0]->getColisionBounds()));
        }
        if(mBoxes[i]->getPosition().y <= 100 - mBoxes[i]->getSize().y/2) {

            if(mBoxes[i]->getColor() == (sf::Color(200,0,0,250))) ++mGood_bad.x;
            else ++mGood_bad.y;

            do{
                int posx = rand()%(int)(gameSize.x -210 - mBoxes[i]->getSize().x) +mBoxes[i]->getSize().x;
                int posy = rand()%(int)(gameSize.y -100 - 2*mBoxes[i]->getSize().x) +mBoxes[i]->getSize().y +100;
                int ran = rand()%2;
                mGoodBoxes[i] = ran;
                if(ran == 0) mBoxes[i]->setColor(sf::Color(200,0,0,250));
                else mBoxes[i]->setColor(sf::Color(0,200,0,250));
                mBoxes[i]->setPosition(sf::Vector2f(posx, posy));
            }while(mBoxes[1]->getColisionBounds().intersects(mBoxes[0]->getColisionBounds()));

        }
    }

    mText->setString("Be: " + std::to_string(mGood_bad.x) + " Malament: " + std::to_string(mGood_bad.y));

    if(mGood_bad.x - mGood_bad.y >= qttyToEnd){
        //std::cout << "Penguin" << std::endl;
        //canvia l'estat
        requestStackPop();
        requestNextState();
    }

    return true;
}

void MinigaemFitIt::handleRealtimeInput(){

    bool moving = false;
    mPlayer->setVel(0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up   ) ) {
        mPlayer->setVel(mPlayer->getVel().x,mPlayer->getVel().y-movVel);
        mPlayer->setDir(dir_up); moving = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down ) ) {
        mPlayer->setVel(mPlayer->getVel().x,mPlayer->getVel().y+movVel);
        mPlayer->setDir(dir_down); moving = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left ) ) {
        mPlayer->setVel(mPlayer->getVel().x-movVel,mPlayer->getVel().y);
        mPlayer->setDir(dir_left); moving = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ) {
        mPlayer->setVel(mPlayer->getVel().x+movVel,mPlayer->getVel().y);
        mPlayer->setDir(dir_right); moving = true;
    }
    if(! moving) {
        mPlayer->setVel(0,0);
        mPlayer->setDir(dir_none);
    }

}

bool MinigaemFitIt::handleEvent(const sf::Event& event) {

    // Game input handling
    //CommandQueue& commands = mWorld.getCommandQueue();
    //mPlayer.handleEvent(event, commands);

    // Escape pressed, trigger the pause screen
    //if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    //    requestStackPush(States::Pause);

    return true;
}
