/****************************************** MAIN.CPP ***************************************************************/

#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

int main(){

	//VARIABLES	(Basic)


	//VARIABLES (Objects)
	sf::Event event;

	//VARIABLES (Vectors)
	sf::Vector2u windowSize(1100,700); 

	//CREATE THE WINDOW
	// for having it in fullScreen the first parameter will be sf::VideoMode::getDesktopMode().
	// in the second parameter the L prefix denotes a wide character/string (it will be a W_char which is encoded with more bytes and so there can be accents)
	sf::RenderWindow window(sf::VideoMode(size.x,size.y), L"1714: La resistència de l'Història", sf::Style::Resize|sf::Style::Close);


	//GAME LOOP
	while(window.isOpen()){

		//EVENT HANDLER LOOP
		while(window.pollEvent(event)){

			switch (event.type){
			
				//Close window event
				case sf::Event::Closed:
					window.close();
					break;
			
				//KeyPressed event
				case  sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::X) {
						//stuff to do if X key is pressed
					}
				break;

				//Resize event
				case sf::Event::Resized:
					//updating the size of the window
					windowSize.x = event.size.width;
					windowSize.y = event.size.height;
					//and setting the new size
					try { window.setSize(windowSize); }
					catch(sf::Event e){	std::cout << "Broken on resizing : ( " << std::endl; }
					break;

				//Mouse Button Pressed event
				case sf::Event::MouseButtonPressed:
					//if the button is left
					if (event.mouseButton.button == sf::Mouse::Left) {
						//if we want the place where it have been pressed, it will be on
						//event.mouseButton.x , event.mouseButton.y
					}

				//No more events to handle
				//for more events http://www.sfml-dev.org/documentation/2.1/classsf_1_1Event.php
				default:
					break;
			}
		}
	}
}