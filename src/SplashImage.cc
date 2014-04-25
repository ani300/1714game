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
            //read the text that will be displayed (and read again if there is a %)
            getline(infile, text); while(tex[0] == '%') getline(infile, text);
            //read the X position of the text (and read again if there is a %)
            getline(infile, textPosX); while(tex[0] == '%') getline(infile, textPosX);
            //read the Y position of the text (and read again if there is a %)
            getline(infile, textPosY); while(tex[0] == '%') getline(infile, textPosY);
            //save the position that are on strings in a Vector2f
            textPosition(atoi(textPosX.c_str()), atoi(textPosY.c_str()));
            //set text, font and size to escriptura
            escriptura  = sf::Text(text,mFont,20);

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
	escriptura.setPosition(textPosition);
	
	//draw drawable things
	window.draw(sprite);
    window.draw(escriptura);
}
