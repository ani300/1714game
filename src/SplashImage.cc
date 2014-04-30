/*********************************SplashImage.cpp***********************************/
#include "SplashImage.h"

//Constructor
SplashImage::SplashImage(sf::RenderWindow &window) : DrawableObject(window) {

}

std::wstring SplashImage::utf8_to_utf16(const std::string& utf8)
{
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

//Constructor with name of the image it want's to display
SplashImage::SplashImage(sf::RenderWindow &window, std::string document): DrawableObject(window) {
    std::stringstream s;

    mFont.loadFromFile("res/media/Sansation.otf");
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

    loadTexture(tex.c_str());
    setTextureToSprite();

    windowSize.x = window.getSize().x; windowSize.y = window.getSize().y;
    sf::Vector2f escala(float(windowSize.y)/float(texture.getSize().y), float(windowSize.y)/float(texture.getSize().y));
    setScaleToSprite(escala);
    
    //centrar la pantalla
    setPosition(sf::Vector2f((windowSize.x-texture.getSize().x*escala.x)/2, 0.0f));


    //number of texsts we want to write in this splash immage
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

}

//Destructor
SplashImage::~SplashImage(){
}

void SplashImage::draw(){
    DrawableObject::draw();
    window.draw(escriptura);
}

void SplashImage::draw(sf::RenderWindow &Wind){
	//set sprite values
    sprite.setTexture(texture);
    sprite.setPosition(position.x, position.y);
    //set text values
    for(int i = 0; i < textos.size(); ++i)	textos[i].setPosition(positions[i]);	
	
	//draw drawable things
	window.draw(sprite);
	for(int i = 0; i < textos.size(); ++i)	window.draw(textos[i]);

}
