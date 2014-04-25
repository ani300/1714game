/*********************************SplashImage.cpp***********************************/
#include "SplashImage.h"

//Constructor
SplashImage::SplashImage(sf::RenderWindow &window) : DrawableObject(window) {

}

//Constructor with name of the image it want's to display
SplashImage::SplashImage(sf::RenderWindow &window, std::string document): DrawableObject(window) {
	std::stringstream s;
    sf::Font mFont;
    mFont.loadFromFile("res/media/Sansation.ttf");
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
    sf::Vector2f escala(windowSize.x/texture.getSize().x, windowSize.x/texture.getSize().x);
    setScaleToSprite(escala);
    
    //centrar la pantalla
    setPosition(sf::Vector2f((windowSize.x-texture.getSize().x*escala.x)/2, (float)0.0));



    std::string num_text;
    getline(infile, num_text); while(tex[0] == '%') getline(infile, num_text);
    int numText = atoi(num_text.c_str());

    for(int i = 0; i < numText; ++i){

            std::string text, textPosX, textPosY;
            getline(infile, text); while(tex[0] == '%') getline(infile, text);
            getline(infile, textPosX); while(tex[0] == '%') getline(infile, textPosX);
            getline(infile, textPosY); while(tex[0] == '%') getline(infile, textPosY);
            sf::Vector2f textPosition(atoi(textPosX.c_str()), atoi(textPosY.c_str()));
            escriptura  = sf::Text(text,mFont,20);

            //void 	setFont (const Font &font)
            //void 	setPosition (const Vector2f &position)
            //void 	setScale (float factorX, float factorY)
            //CARREGAR UNA FONT I POSAR-LI LA POSICIO textPosition i el qeu faci falta

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
    sprite.setTexture(texture);
    sprite.setPosition(position.x, position.y);
    window.draw(sprite);

    window.draw(escriptura);
}
