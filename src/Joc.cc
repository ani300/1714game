#include "Joc.h"


//Constructor
Joc::Joc() : window(sf::VideoMode::getDesktopMode() , L"1714: La resistència de l'Història", sf::Style::Resize|sf::Style::Close), graphic(window) {
    
}

void Joc::processEvents() {
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		window.close();
	}
}

void Joc::update() {

}

void Joc::render() {
	window.clear();
	window.display();
}

int Joc::play() {

    //GAME LOOP
    while(window.isOpen()){
    	processEvents();
    	update();
    	render();
    }
    return EXIT_SUCCESS;
}
