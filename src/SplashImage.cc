/*********************************SplashImage.cpp***********************************/
#include "SplashImage.h"

//Constructor
SplashImage::SplashImage(sf::RenderWindow &window) : DrawableObject(window) {

}

//Constructor with name of the image it want's to display
SplashImage::SplashImage(sf::RenderWindow &window, std::string document): DrawableObject(window) {
	std::stringstream s;
	s << "res/document/" << document << std::endl;
	std::cerr << "res/document/" << document << " obert " << std::endl; 
	getline(s, str);
	
	std::string tex;
	std::ifstream infile;
	infile.open (str.c_str());
	getline(infile, tex);
	while(tex[0] == '%') getline(infile, tex); 
	std::stringstream t;
	t << "res/pictures/" << tex << std::endl;
		std::cerr << "res/pictures/" << tex << " agafada " << std::endl;
	//getline(t, tex);
	loadTexture(tex.c_str());
	setTextureToSprite();
	sf::Vector2f escala(1,1);
	//POSAR VALORS A ESCALA PERQUE OCUPI TOTA LA PANTALLA
	setScaleToSprite(escala);

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
	
	setPosition(sf::Vector2f(0, 0));
}

//Destructor
SplashImage::~SplashImage(){
}

void SplashImage::draw(){
	DrawableObject::draw();
	window.draw(sftext);
}