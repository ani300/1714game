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
	// For having it in fullScreen the first parameter will be sf::VideoMode::getDesktopMode().
	// In the second parameter the L prefix denotes a wide character/string 
	// (it will be a W_char which is encoded with more bytes and so there can be accents).
	sf::RenderWindow window(sf::VideoMode(size.x,size.y), L"1714: La resistència de l'Història", sf::Style::Resize|sf::Style::Close);


	//MUSIC
	/* If we want music, we will only have to do these.
	sf::Music music;
	if (!music.openFromFile("music/GameSong1.ogg")) 
		std::cout << " Can't load the song " << std::endl;
	music.play();
	music.setPitch(1);
	music.setLoop(true);
	*/

	//we would have to create a graphic class withe the window as a parameter so it can write on it. 
		// the constructor of the class will be something like Class::Class(sf::RenderWindow &window) :windowGame(window) { }
		// where windowGame will have to be the sf::RenderWindow that the class will have as a parameter. 
		// the :windowGame(window) means: When you are using these constructor, as default initialize windowGame with the 
		// value of 'window' (which is the parameter we are using to create the Class).

	//we would have to create later a class lvl or something I still don't know how we sould do that -_- 
		//and it's late and i have to sleep, so good night <3

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
						//Stuff to do if X key is pressed
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
			}//switch case end

		} //event loop end

	} //window.open() end

} //main end