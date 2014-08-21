/******************************Fight.cpp**********************************/
#include "Fight.h"

//Constructor
Fight::Fight(PilaEstats& stack, Context context)
: Estat(stack, context)
, mPlayer(nullptr)
, mText(nullptr) {

}

Fight::Fight(PilaEstats& stack, Context context, std::string document)
: Estat(stack, context)
, mPlayer(nullptr)
, mText(nullptr) {

    std::string tex;
    std::ifstream infile;

    std::stringstream s;
    s << "res/documents/" << document;
    std::cerr << s.str() << std::endl;
    infile.open (s.str());
    if(!infile.is_open()) std::cerr << "No puc obrir el document del Minigaem Fight!" << std::endl;
        
    // CARREGA TEXTURES

    //Textura fons
    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    mOwnTextures.load(Textures::FightBackground, Utils::getTexturePath(tex));
    
    //Textura player
    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    mOwnTextures.load(Textures::FightPlayer, Utils::getTexturePath(tex));

    //Textura ground enemy
    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    mOwnTextures.load(Textures::FightGroundEnemy, Utils::getTexturePath(tex));

    //Textura small air enemy
    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    mOwnTextures.load(Textures::FightSmallAirEnemy, Utils::getTexturePath(tex));

    //Textura big air enemy
    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    mOwnTextures.load(Textures::FightBigAirEnemy, Utils::getTexturePath(tex));
    
    // CREACIÓ ESCENA
    // Inicialitza les dues capes
    for (std::size_t i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    // Prepara el fons de pantalla i la font
    sf::Texture& backTexture = mOwnTextures.get(Textures::FightBackground);
    sf::Texture& playerTexture = mOwnTextures.get(Textures::FightPlayer);
    sf::Font& font = getContext().fonts->get(Fonts::Sansation);

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
    std::unique_ptr<FightScreenPlayer> playerNode(new FightScreenPlayer(playerTexture));
    mPlayer = playerNode.get();
    mPlayer->setSize(sf::Vector2u(100, 200));
    mSceneLayers[Objects]->attachChild(std::move(playerNode));

    // Agafa tots els enemics que apareixeran
    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    nEnemies = atoi(tex.c_str());
    std::cout << nEnemies << std::endl;

    for(int b = 0; b < nEnemies; ++b) {
        // Llegeix la línia d'informació
        getline(infile, tex);
        while(tex[0] == '%') getline(infile, tex);
        std::stringstream ss;
        ss << tex;
        int ms, pos;
        int big;
        ss >> ms >> pos;
        if (pos > 0 && pos < 4) {
            ss >> big;
        }

        // Crea el timer d'enemic
        Timer t;
        t.temps = sf::Clock();
        t.pos = pos;
        t.ms = ms;
        if (pos > 0 && pos < 4) {
            t.isBig = big;
        }
        mTimers.push_back(t);
    }
}

void Fight::draw() {
    // Print texts
    getContext().rTexture->draw(mSceneGraph);
}

bool Fight::update(sf::Time dt) {
    sf::Texture& groundEnemyTexture = mOwnTextures.get(Textures::FightGroundEnemy);
    sf::Texture& airSmallEnemyTexture = mOwnTextures.get(Textures::FightSmallAirEnemy);
    sf::Texture& airBigEnemyTexture = mOwnTextures.get(Textures::FightBigAirEnemy);
    handleRealtimeInput(); // NOPE
    // Mira si s'ha de crear algun enemic nou
    int i = 0;
    while (i < mTimers.size()) {
        sf::Time elapsed = mTimers[i].temps.getElapsedTime();
        if (elapsed.asMilliseconds() > mTimers[i].ms) {
            // Crea l'enemic
            sf::Texture& enemyTexture = groundEnemyTexture;
            switch(mTimers[i].pos) {
            case 0:
            case 4:
                enemyTexture = groundEnemyTexture;
                break;
            case 1:
            case 2:
            case 3:
            default:
                if (mTimers[i].isBig) {
                    enemyTexture = airBigEnemyTexture;
                }
                else {
                    enemyTexture = airSmallEnemyTexture;
                }
                break;
            }

            std::unique_ptr<FightScreenEnemy> enemyNode(new FightScreenEnemy(enemyTexture));
            Enemy e;
            e.temps = sf::Clock();
            e.actualStep = 0;
            e.object = enemyNode.get();

            // Tria la posició on comença cada un
            switch(mTimers[i].pos) {

            }

            e.object->setPosition(500.0f+rand()%300, 500.0f+rand()%300);
            mEnemies.push_back(e);

            mSceneLayers[Objects]->attachChild(std::move(enemyNode));

            mTimers.erase(mTimers.begin() + i);
        }
        else {
            ++i;
        }
    }
    mSceneGraph.update(dt);
    return true;
}

void Fight::handleRealtimeInput() { 
}

bool Fight::handleEvent(const sf::Event& event) {
    return true;
}
