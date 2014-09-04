/******************************MinigaemFitIt.cpp**********************************/
#include "WalkMap.h"

//Constructor
WalkMap::WalkMap(PilaEstats& stack, Context context)
: Estat(stack, context)
, mPlayer(nullptr)
, mText(nullptr) {

}

WalkMap::WalkMap(PilaEstats& stack, Context context, std::string document)
: Estat(stack, context)
, mPlayer(nullptr)
, mText(nullptr)
{

    std::string tex;
    std::ifstream infile;

    std::stringstream s;
    s << "res/documents/" << document;
    std::cerr << s.str() << std::endl;
    infile.open (s.str());
    if(!infile.is_open()) std::cerr << "No puc obrir el document del WM" << std::endl;

    // CARREGA TEXTURES

    //Textura fons
    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    mOwnTextures.load(Textures::WMBackground, Utils::getTexturePath(tex));

    //Textura player
    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    mOwnTextures.load(Textures::WMPlayer, Utils::getTexturePath(tex));

    // CREACIÓ ESCENA
    // Inicialitza les dues capes
    for (std::size_t i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    // Prepara el fons de pantalla i la font
    sf::Texture& backTexture = mOwnTextures.get(Textures::WMBackground);
    sf::Texture& playerTexture = mOwnTextures.get(Textures::WMPlayer);
    sf::Font& font = getContext().fonts->get(Fonts::Sansation);
    mText = new TextNode(font, "Penguin <3");
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
    mPlayer->setSize(sf::Vector2u(100*4, 200*8));
    mSceneLayers[Boxes]->attachChild(std::move(playerNode));

    // PREPARA TOTS ELS OBJECTES
    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    int itmQtty = atoi(tex.c_str());
    std::cout << itmQtty << " items" << std::endl;

    for(int b = 0; b < itmQtty; ++b) {
        // Carrega
        getline(infile, tex);
        while(tex[0] == '%') getline(infile, tex);
        mItemTextures.load(b, Utils::getTexturePath(tex));

        // Crea
        std::unique_ptr<Box> boxNode(new Box(mItemTextures.get(b)));
        mItems.push_back(boxNode.get());
        //mBoxes[b]->setSize(sf::Vector2u(200, 200));

        // Posició
        getline(infile, tex);
        while(tex[0] == '%') getline(infile, tex);
        int posx = atoi(tex.c_str());
        getline(infile, tex);
        while(tex[0] == '%') getline(infile, tex);
        int posy = atoi(tex.c_str());
        mItems[b]->setPosition(sf::Vector2f(posx,posy));
        mItems[b]->setSize(sf::Vector2u(200, 200));

        // posa-la a la llista de coses a pintar
        mSceneLayers[Boxes]->attachChild(std::move(boxNode));
    }

    //TODO: PREPARA TOTS ELS PNJs
    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    int pnjQtty = atoi(tex.c_str());
    std::cout << pnjQtty << " pnjs" << std::endl;

    for(int b = 0; b < pnjQtty; ++b) {
        // Carrega la textura
        getline(infile, tex);
        while(tex[0] == '%') getline(infile, tex);
        mPnjTextures.load(b, Utils::getTexturePath(tex));

        // Crea
        std::unique_ptr<Box> boxNode(new Box(mPnjTextures.get(b)));
        mPnjs.push_back(boxNode.get());
        //mBoxes[b]->setSize(sf::Vector2u(200, 200));

        // Posició
        getline(infile, tex);
        while(tex[0] == '%') getline(infile, tex);
        int posx = atoi(tex.c_str());
        getline(infile, tex);
        while(tex[0] == '%') getline(infile, tex);
        int posy = atoi(tex.c_str());
        mPnjs[b]->setPosition(sf::Vector2f(posx,posy));
        mPnjs[b]->setSize(sf::Vector2u(200, 200));
        mPnjs[b]->setMovility(false);

        //text qeu dirà en parlar-hi
        getline(infile, tex);
        while(tex[0] == '%') getline(infile, tex);
        mPnjs[b]->setText(tex);

        // posa-la a la llista de coses a pintar
        mSceneLayers[Boxes]->attachChild(std::move(boxNode));
    }

    // CREAR LA VIEW
        //ho he posat al draw

}

void WalkMap::draw() {
    // Print texts
//    getContext().rTexture->draw(mSceneGraph);

    sf::Vector2f viewPosition (0,0);
    sf::Vector2f playerPosition (mPlayer->getPosition());
    view.reset(sf::FloatRect(playerPosition.x,playerPosition.y,
                                     getContext().rTexture->getSize().x*0.62,
                                     getContext().rTexture->getSize().y*0.62));
    //if(playerPosition.y+10 > view.getSize().y/2)
   //     viewPosition.y = playerPosition.y+10;
    //else
    viewPosition.y = view.getSize().y/2;
    viewPosition.x = view.getSize().x/2;
    view.setCenter(playerPosition);
    view.setViewport(sf::FloatRect(0,0,1.0f,1.0f));

    getContext().rTexture->setView(view);
    getContext().rTexture->draw(mSceneGraph);

}

bool WalkMap::update(sf::Time dt) {

    handleRealtimeInput();

    sf::Vector2f nextPlayerPosition;
    nextPlayerPosition.x = mPlayer->getPosition().x + mPlayer->getVel().x * dt.asSeconds();
    nextPlayerPosition.y = mPlayer->getPosition().y + mPlayer->getVel().y * dt.asSeconds();

    sf::Vector2f playerColisionSize( mPlayer->getColisionBounds().width, mPlayer->getColisionBounds().height);
    sf::FloatRect movedBoxRect;
    sf::FloatRect movedRect (nextPlayerPosition, playerColisionSize);

    if(movedRect.intersects(mItems[0]->getColisionBounds())){
        mPlayer->setVel(mPlayer->getVel().x/2,mPlayer->getVel().y/2);
        mItems[0]->setVel(1.0f * mPlayer->getVel());
        movedBoxRect = mItems[0]->getColisionBounds();
        movedBoxRect.left = mItems[0]->getPosition().x + mItems[0]->getVel().x * dt.asSeconds();
        movedBoxRect.top = mItems[0]->getPosition().y + mItems[0]->getVel().y * dt.asSeconds();
        if(movedBoxRect.intersects(mItems[1]->getColisionBounds()))
            mItems[1]->setVel(1.0f * mPlayer->getVel());
    }
    if(movedRect.intersects(mItems[1]->getColisionBounds())){
        mPlayer->setVel(mPlayer->getVel().x/2,mPlayer->getVel().y/2);
        mItems[1]->setVel(1.0f * mPlayer->getVel());
        movedBoxRect = mItems[1]->getColisionBounds();
        movedBoxRect.left = mItems[1]->getPosition().x + mItems[1]->getVel().x * dt.asSeconds();
        movedBoxRect.top = mItems[1]->getPosition().y + mItems[1]->getVel().y * dt.asSeconds();
        if(movedBoxRect.intersects(mItems[0]->getColisionBounds()))
            mItems[0]->setVel(1.0f * mPlayer->getVel());
    }

    mSceneGraph.update(dt);

    //check if player is in the game and correct it if not
    if(mPlayer->getPosition().y < 0) mPlayer->setPosition(mPlayer->getPosition().x, 0);
    if(mPlayer->getPosition().y > getContext().rTexture->getSize().y - mPlayer->getSize().y)
        mPlayer->setPosition(mPlayer->getPosition().x, getContext().rTexture->getSize().y - mPlayer->getSize().y);

//    //Check boxes are in the game
//    for(int i = 0; i < mBoxes.size(); ++i) {
//        if(mBoxes[i]->getPosition().x >= gameSize.x - mBoxes[i]->getSize().x) {

//            if(mBoxes[i]->getColor() == (sf::Color(0,200,0,250))) ++mGood_bad.x;
//            else ++mGood_bad.y;

//            do{
//                int posx = rand()%(int)(gameSize.x -210 - mBoxes[i]->getSize().x) +mBoxes[i]->getSize().x;
//                int posy = rand()%(int)(gameSize.y -100 - 2*mBoxes[i]->getSize().x) +mBoxes[i]->getSize().y +100;
//                int ran = rand()%2;
//                mGoodBoxes[i] = ran;
//                if(ran == 0) mBoxes[i]->setColor(sf::Color(200,0,0,250));
//                else mBoxes[i]->setColor(sf::Color(0,200,0,250));
//                mBoxes[i]->setPosition(sf::Vector2f(posx, posy));
//            }while(mBoxes[1]->getColisionBounds().intersects(mBoxes[0]->getColisionBounds()));
//        }
//        if(mBoxes[i]->getPosition().y <= 100 - mBoxes[i]->getSize().y/2) {

//            if(mBoxes[i]->getColor() == (sf::Color(200,0,0,250))) ++mGood_bad.x;
//            else ++mGood_bad.y;

//            do{
//                int posx = rand()%(int)(gameSize.x -210 - mBoxes[i]->getSize().x) +mBoxes[i]->getSize().x;
//                int posy = rand()%(int)(gameSize.y -100 - 2*mBoxes[i]->getSize().x) +mBoxes[i]->getSize().y +100;
//                int ran = rand()%2;
//                mGoodBoxes[i] = ran;
//                if(ran == 0) mBoxes[i]->setColor(sf::Color(200,0,0,250));
//                else mBoxes[i]->setColor(sf::Color(0,200,0,250));
//                mBoxes[i]->setPosition(sf::Vector2f(posx, posy));
//            }while(mBoxes[1]->getColisionBounds().intersects(mBoxes[0]->getColisionBounds()));

//        }
//    }

//    mText->setString("Caixes ben posades: " + std::to_string(mGood_bad.x - mGood_bad.y));

    return true;
}

void WalkMap::handleRealtimeInput(){

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

bool WalkMap::handleEvent(sf::Event const&){
    return true;
}
