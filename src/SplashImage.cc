/*********************************SplashImage.cpp***********************************/
#include "SplashImage.h"

//Constructor
SplashImage::SplashImage(){

}

//Constructor with name of the image it want's to display
SplashImage::SplashImage(std::string document){
	std::stringstream s;
	s << "res/document/" << document;
	str = s.c_str();
	
	string tex;
	ifstream infile;
	infile.open (str);
	getline(infile, tex);
	while(tex[0] == '%') getline(infile, tex); 
	std::stringstream t;
	t << "res/pictures/" << tex;
	loadTexture(t.c_str());
	setTextureToSprite();
	sf::Vector2f escala(1,1);
	//POSAR VALORS A ESCALA PERQUE OCUPI TOTA LA PANTALLA
	setScaleToSprite(escala);

	string text, textPosX, textPosY;
	getline(infile, text); while(tex[0] == '%') getline(infile, text); 
	getline(infile, text); while(tex[0] == '%') getline(infile, text); 
	getline(infile, text); while(tex[0] == '%') getline(infile, text); 
	sf::Vector2f textPosition(atoi(textPosX.c_str()), atoi(textPosY.c_str()));
	sftext.setString(text);
	//void 	setFont (const Font &font)
	//void 	setPosition (const Vector2f &position)
	//void 	setScale (float factorX, float factorY)
	//CARREGAR UNA FONT I I POSAR-LI LA POSICIO textPosition i el qeu faci falta
}

//Destructor
SplashImage::~SplashImage(){
}

void SplashImage::draw(sf::RenderWindow& window){
	window.draw(sprite);
	window.draw(sftext);
}