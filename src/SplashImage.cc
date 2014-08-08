/*********************************SplashImage.cpp***********************************/
#include "SplashImage.h"

SplashImage::SplashImage(PilaEstats& stack, Context context)
: Estat(stack, context) {

}

SplashImage::SplashImage(PilaEstats& stack, Context context, std::string document)
: Estat(stack, context) {

    std::stringstream s;

    s << "res/documents/" << document << std::endl;
    getline(s, str);
    std::string tex;
    std::ifstream infile;
    infile.open(str);

    if(!infile.is_open()) std::cerr << "No puc obrir el document de l'SplashImage" << std::endl;

    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    std::stringstream t;
    t << "res/pictures/" << tex << ".png";

    // CARREGA TEXTURES EXTRA
    mOwnTextures.load(Textures::SplashImage::Fons, t.str());

    // CREACIÓ ESCENA
    // Inicialitza les dues capes
    for (std::size_t i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    // Prepara el fons de pantalla i la font
    sf::Texture& texture = mOwnTextures.get(Textures::SplashImage::Fons);
    sf::Font& font = getContext().fonts->get(Fonts::AlluraRegular);

    // Add the background sprite to the scene
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture));

    //centrar la pantalla i escalar la imatge
    float esc = float(gameSize.x)/float(texture.getSize().x);
    backgroundSprite->setScale(sf::Vector2f(esc, esc));
    backgroundSprite->setPosition(sf::Vector2f(0.0f, (gameSize.y-texture.getSize().y*esc)/2));
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

    // Afegeix els textos
    std::string num_text;
    getline(infile, num_text); while(num_text[0] == '%') getline(infile, num_text);
    int numText = atoi(num_text.c_str());

    for(int i = 0; i < numText; ++i){
        std::string text, textPosX, textPosY;
        //read the text that will be displayed (and read again if there is a %)
        getline(infile, text); while(text[0] == '%') getline(infile, text);
        //read the X position of the text (and read again if there is a %)
        getline(infile, textPosX); while(textPosX[0] == '%') getline(infile, textPosX);
        //read the Y position of the text (and read again if there is a %)
        getline(infile, textPosY); while(textPosY[0] == '%') getline(infile, textPosY);
        //save the position that are on strings in a Vector2f
        sf::Vector2f textPosition = sf::Vector2f(float(atoi(textPosX.c_str())), float(atoi(textPosY.c_str())));

        //set text, font and size to escriptura
        std::cout << text << std::endl;
        std::unique_ptr<TextNode> textNode(new TextNode(font, text));
        textNode->setPosition(textPosition);
        textNode->setCharacterSize(50);
        textNode->setColor(sf::Color::Red);
        mSceneLayers[Text]->attachChild(std::move(textNode));
    }

    // define a 120x50 rectangle
    fletxaRect = sf::RectangleShape(sf::Vector2f(300, 150));

    // change the size to 100x100
    fletxaRect.setPosition(sf::Vector2f(1620, 930));
}

void SplashImage::draw() {
    // Print texts
    getContext().rTexture->draw(mSceneGraph);
    getContext().rTexture->draw(fletxaRect);
}

bool SplashImage::update(sf::Time dt) {
    // Arreglar input
    /*if (mouseBut == mouse_left) {
        sf::Vector2f mouseBo;
        mouseBo.x = mouseClick.x * 1.0/getContext().escala.x;
        mouseBo.y = mouseClick.y * 1.0/getContext().escala.y;
        if (mouseBo.x > 1620 and mouseBo.y > 930) {
            requestNextState(); // Aquí és on es canvia al següent estat
        }
        mouseBut = mouse_none;
    }*/
    //mWorld.update(dt);

    //CommandQueue& commands = mWorld.getCommandQueue();
    //mPlayer.handleRealtimeInput(commands);

    return true;
}

bool SplashImage::handleEvent(const sf::Event& event)
{
    // Game input handling
    //CommandQueue& commands = mWorld.getCommandQueue();
    //mPlayer.handleEvent(event, commands);

    // Escape pressed, trigger the pause screen
    //if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    //    requestStackPush(States::Pause);

    return true;
}
