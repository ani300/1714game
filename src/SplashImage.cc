/*********************************SplashImage.cpp***********************************/
#include "SplashImage.h"

//Constructor
SplashImage::SplashImage(sf::RenderWindow &window) : DrawableObject(window) {

}

//Constructor with name of the image it want's to display
SplashImage::SplashImage(sf::RenderWindow &window, std::string document): DrawableObject(window) {
	std::stringstream s;
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

    windowSize.x = window.getSize().x;
    windowSize.y = window.getSize().y;
    sf::Vector2f escala(windowSize.x/texture.getSize().x, windowSize.x/texture.getSize().x);
    //sf::Vector2f escala(1,1);
   // sf::Vector2f escala(2,2);
    setPosition(sf::Vector2f((windowSize.x-texture.getSize().x*escala.x)/2, (float)0.0));
    //centrar la pantalla
	setScaleToSprite(escala);


    /*
    llegir num de texts que volem escriure

        per cada un
            llegir text, posx, posy

    */
/*	std::string text, textPosX, textPosY;
	getline(infile, text); while(tex[0] == '%') getline(infile, text); 
	getline(infile, text); while(tex[0] == '%') getline(infile, text); 
	getline(infile, text); while(tex[0] == '%') getline(infile, text); 
	sf::Vector2f textPosition(atoi(textPosX.c_str()), atoi(textPosY.c_str()));
	sftext.setString(text);
*/	//void 	setFont (const Font &font)
	//void 	setPosition (const Vector2f &position)
	//void 	setScale (float factorX, float factorY)
	//CARREGAR UNA FONT I POSAR-LI LA POSICIO textPosition i el qeu faci falta
}

//Destructor
SplashImage::~SplashImage(){
}

void SplashImage::draw(){
	DrawableObject::draw();
	window.draw(sftext);
}
