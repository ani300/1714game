#include <cstdio>
#include <string>
#include <fstream>
#include "Joc.h"

//Constructor
Joc::Joc() : window(sf::VideoMode::getDesktopMode() , L"1714: La resistència de l'Història"
	, sf::Style::Resize|sf::Style::Close) {

}

void Joc::processEvents() {
	sf::Event event;
	while(window.pollEvent(event)) {
		switch(event.type) {
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code,true);
				break;
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code,false);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) mouseButton = left;
				else if (event.mouseButton.button == sf::Mouse::Right) mouseButton = right;
				mouseClick.x = event.mouseButton.x;
				mouseClick.y = event.mouseButton.y;
				break;
			case sf::Event::Closed:
				window.close();
				break;
		}
	}
}

void Joc::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {

	dir = none;
	if(isPressed){
		if (isPressed && key == sf::Keyboard::W) dir = up;
		if (isPressed && key == sf::Keyboard::S) dir = down;
		if (isPressed && key == sf::Keyboard::A) dir = left;
		if (isPressed && key == sf::Keyboard::D) dir = right;
	}
	
	
}

void Joc::update(sf::Time elapsedTime) {
	for(int i = 0; i < drawableObjects.size(); ++i){
		
		if(dir != none) { //THERE IS MOVEMENT	
			sf::Vector2f movement(0.f,0.f);
			movement.x = dirx[dir] * elapsedTime.asSeconds();
			movement.y = diry[dir] * elapsedTime.asSeconds();
			drawableObjects[i].move(movement);
			dir = none;
		}
		if(mouseButton != none){
			drawableObjects[i].click(mouseButton, mouseClick);
			mouseButton = none;
		}
		
	}
}

void Joc::render() {
	window.clear();
	for(int i = 0; i < drawableObjects.size(); ++i){
		drawableObjects[i].draw(window);
	}
	window.display();
}

void readNextState(int& skipLines){
	string doc;
	ifstream infile;
	infile.open ("res/document/Joc.txt");
	for(int i = 0; i < skipLines; ++i) getline(infile,doc); // Saves the line in STRING.
	//% means this line is a comment
	while(doc[0] == '%') {
		getline(infile,doc);
		++skipLines;
	}
	
	switch(doc[0]){
		case 'S' :
			SplashImage splashIm(doc);
			//buidar drawableObjects;
			drawableObjects.push_back(splashIm);
			break;
		case 'X' :
			break;
		default:
			break;
	}
	infile.close();
}

int Joc::play() {
	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	int skipLines = 0;
	readNextState(skipLines);
	
	window.setVerticalSyncEnabled(true);
	while(window.isOpen()) {

		ifstream estatFile;
		estatFile.open("res/documents/Status.txt");
		string stat;
		getline(estatFile,stat);
		estatFile.close();
		if(stat == "OK") {
			//delete OK from estatFile
			readNextState(skipLines);
		}
		
		processEvents();
		timeSinceLastUpdate += clock.restart();

		while(timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
	return EXIT_SUCCESS;
}
