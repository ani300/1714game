/*********************************SplashImage.cpp***********************************/
#include "SplashImage.h"

//Constructor
SplashImage::SplashImage(sf::RenderWindow &window) : DrawableObject(window) {

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
            escriptura.setString(sf::String(text));
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
