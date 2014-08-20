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

    // CARREGA TEXTURES EXTRA
    mOwnTextures.load(Textures::SplashImage::Fons, Utils::getTexturePath(tex));
    mOwnTextures.load(Textures::SplashImage::Fletxa, Utils::getTexturePath("putafletxa"));

    // CREACIÓ ESCENA
    // Inicialitza les dues capes
    for (std::size_t i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    // Prepara el fons de pantalla i la font
    sf::Texture& texture = mOwnTextures.get(Textures::SplashImage::Fons);
    sf::Texture& fletxaTexture = mOwnTextures.get(Textures::SplashImage::Fletxa);
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
    // Add the background sprite to the scene
    std::unique_ptr<SpriteNode> fletxaSprite(new SpriteNode(fletxaTexture));

    //centrar la pantalla i escalar la imatge
    fletxaSprite->setPosition(sf::Vector2f(1620, 880));
    mSceneLayers[Text]->attachChild(std::move(fletxaSprite));
}

void SplashImage::draw() {
    // Print texts
    getContext().rTexture->draw(mSceneGraph);
}

bool SplashImage::update(sf::Time dt) {
    // WOLOLO DO THINGS
    mSceneGraph.update(dt);
    return true;
}

bool SplashImage::handleEvent(const sf::Event& event) {
    switch (event.type) {
        // Clic del ratolí
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = Utils::correctMouse(
                    sf::Vector2i(event.mouseButton.x, event.mouseButton.y),
                    getContext().escala);
                std::cout << mousePos.x << " " << mousePos.y << std::endl;
                if (mousePos.x > 1620 and mousePos.y > 880) {
                    requestStackPop();
                    requestNextState();
                }
            }
            break;

        // we don't process other types of events
        default:
            break;
    }
    return true;
}
