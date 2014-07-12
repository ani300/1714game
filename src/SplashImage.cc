/*********************************SplashImage.cpp***********************************/
#include "SplashImage.h"

SplashImage::SplashImage(PilaEstats& stack, Context context, std::string doc)
: Estat(stack, context) {
    std::stringstream s;
    DrawableObject* splashImage = new DrawableObject(*gaemTexture);

    s << "res/documents/" << document << std::endl;
    getline(s, str);
    std::string tex;
    std::ifstream infile;
    infile.open (str);

    if(!infile.is_open()) std::cerr << "No puc obrir el document de l'Splash image" << std::endl;

    getline(infile, tex);
    while(tex[0] == '%') getline(infile, tex);
    std::stringstream t;
    t << "res/pictures/" << tex << std::endl;

    splashImage->loadTexture(tex.c_str());
    splashImage->setTextureToSprite();

    //centrar la pantalla i escalar la imatge
    sf::Texture texture = splashImage->getTexture();
    float esc = float(gameSize.x)/float(texture.getSize().x);
    splashImage->setScaleToSprite(sf::Vector2f(esc, esc));
    splashImage->setPosition(sf::Vector2f(0.0f, (gameSize.y-texture.getSize().y*esc)/2));

    drawableObjects.push_back(splashImage);

    //number of texts we want to write in this splash immage
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
            textPosition = sf::Vector2f((float)atoi(textPosX.c_str()),(float)atoi(textPosY.c_str()));
            // s'ha de guardar aquesta posicio a un vector de posicions (moar pushbacks)
            positions.push_back(textPosition);
            //set text, font and size to escriptura
            std::cout << text << std::endl;
            escriptura.setString(sf::String(utf8_to_utf16(text)));
            escriptura.setFont(mFont);
            escriptura.setCharacterSize(50);
            escriptura.setColor(sf::Color::Red);
            textos.push_back(escriptura);
    }

    // define a 120x50 rectangle
    fletxaRect = sf::RectangleShape(sf::Vector2f(300, 150));

    // change the size to 100x100
    fletxaRect.setPosition(sf::Vector2f(1620, 930));
}

void SplashImage::draw()
{
    mWorld.draw();
}

bool SplashImage::update(sf::Time dt)
{
    mWorld.update(dt);

    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleRealtimeInput(commands);

    return true;
}

bool SplashImage::handleEvent(const sf::Event& event)
{
    // Game input handling
    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleEvent(event, commands);

    // Escape pressed, trigger the pause screen
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        requestStackPush(States::Pause);

    return true;
}


//Destructor
SplashImage::~SplashImage(){
}

void SplashImage::render() {
    Estat::render();

    // Print texts
    //set text values
    for(int i = 0; i < textos.size(); ++i)	textos[i].setPosition(positions[i]);
    //draw drawable things
    for(int i = 0; i < textos.size(); ++i) rTexture->draw(textos[i]);
    rTexture->draw(fletxaRect);

    /*//set sprite values
    sprite.setTexture(texture);
    sprite.setPosition(position.x, position.y);*/
}

void SplashImage::update(sf::Time elapsedTime) {
    if (mouseBut == mouse_left) {
        sf::Vector2f mouseBo;
        mouseBo.x = mouseClick.x * 1.0/escala.x;
        mouseBo.y = mouseClick.y * 1.0/escala.y;
        if (mouseBo.x > 1620 and mouseBo.y > 930) {
            std::ofstream outfile;
            outfile.open("res/documents/Status.txt");
            if(!outfile.is_open()) std::cerr << "res/documents/Status.txt" << " no obert " << std::endl;
            outfile << "OK" << std::endl;
            outfile.close();
        }
        mouseBut = mouse_none;
    }
}

void SplashImage::handlePlayerMouse(mouseButtons mouseButton, sf::Vector2f mouseClick) {
    this->mouseBut = mouseButton;
    this->mouseClick = mouseClick;
}

std::wstring SplashImage::utf8_to_utf16(const std::string& utf8) {
    std::vector<unsigned long> unicode;
    size_t i = 0;
    while (i < utf8.size()) {
        unsigned long uni;
        size_t todo;
        bool error = false;
        unsigned char ch = utf8[i++];
        if (ch <= 0x7F) {
            uni = ch;
            todo = 0;
        }
        else if (ch <= 0xBF) {
            throw std::logic_error("not a UTF-8 string");
        }
        else if (ch <= 0xDF) {
            uni = ch&0x1F;
            todo = 1;
        }
        else if (ch <= 0xEF) {
            uni = ch&0x0F;
            todo = 2;
        }
        else if (ch <= 0xF7) {
            uni = ch&0x07;
            todo = 3;
        }
        else {
            throw std::logic_error("not a UTF-8 string");
        }
        for (size_t j = 0; j < todo; ++j) {
            if (i == utf8.size())
                throw std::logic_error("not a UTF-8 string");
            unsigned char ch = utf8[i++];
            if (ch < 0x80 || ch > 0xBF)
                throw std::logic_error("not a UTF-8 string");
            uni <<= 6;
            uni += ch & 0x3F;
        }
        if (uni >= 0xD800 && uni <= 0xDFFF)
            throw std::logic_error("not a UTF-8 string");
        if (uni > 0x10FFFF)
            throw std::logic_error("not a UTF-8 string");
        unicode.push_back(uni);
    }
    std::wstring utf16;
    for (size_t i = 0; i < unicode.size(); ++i) {
        unsigned long uni = unicode[i];
        if (uni <= 0xFFFF) {
            utf16 += (wchar_t)uni;
        }
        else {
            uni -= 0x10000;
            utf16 += (wchar_t)((uni >> 10) + 0xD800);
            utf16 += (wchar_t)((uni & 0x3FF) + 0xDC00);
        }
    }
    return utf16;
}

