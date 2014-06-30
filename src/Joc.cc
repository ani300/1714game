#include "Joc.h"

//Constructor
Joc::Joc() : window(sf::VideoMode::getDesktopMode(), L"1714: La resistència de l'Història"
	, sf::Style::Titlebar | sf::Style::Close), rTexture() {
	if (!rTexture.create(1920, 1080)) cout << "OPMERDA: No pot crear la RenderTexture" << endl;
	rTexture.setSmooth(true);
    estat = 0;
}

Joc::~Joc() {
    delete estat;
}

void Joc::processEvents() {
	sf::Event event;
	while(window.pollEvent(event)) {
		switch(event.type) {
			case sf::Event::KeyPressed:
                estat->handlePlayerInput(event.key.code,true);
				break;
			case sf::Event::KeyReleased:
                estat->handlePlayerInput(event.key.code,false);
				break;
            case sf::Event::MouseButtonPressed: {
                mouseButtons mouseBut;
                sf::Vector2f mouseClick;
				if (event.mouseButton.button == sf::Mouse::Left) mouseBut = mouse_left;
				else if (event.mouseButton.button == sf::Mouse::Right) mouseBut = mouse_right;
				mouseClick.x = event.mouseButton.x;
				mouseClick.y = event.mouseButton.y;
                estat->handlePlayerMouse(mouseBut, mouseClick);
                break;
            }
			case sf::Event::Closed:
				window.close();
				break;
		}
	}
}

/*void Joc::update(sf::Time elapsedTime) {
	for(int i = 0; i < drawableObjects.size(); ++i){

		if(dir != dir_none) { //THERE IS MOVEMENT	
			sf::Vector2f movement(0.f,0.f);
			movement.x = dirx[dir] * elapsedTime.asSeconds();
			movement.y = diry[dir] * elapsedTime.asSeconds();
			drawableObjects[i]->move(movement);
			dir = dir_none;
		}
		if(mouseBut != mouse_none){
			// Corregir la posició del mouse
			sf::Vector2f mouseBo;
			mouseBo.x = mouseClick.x * 1.0/escala.x;
			mouseBo.y = mouseClick.y * 1.0/escala.y;
			drawableObjects[i]->click(mouseBut, mouseBo);
			mouseBut = mouse_none;
		}
	}
}*/

void Joc::readNextState(int& skipLines){
    std::string doc;
    std::ifstream infile;
    infile.open("res/documents/Joc.txt");
    if(!infile.is_open()) std::cerr << "res/document/Joc.txt" << " no obert " << std::endl;

    for(int i = 0; i < skipLines; ++i) std::getline(infile,doc); // Saves the line in STRING.
	std::getline(infile,doc);
    //% means this line is a comment
	while(doc[0] == '%') {
		std::getline(infile,doc);
		++skipLines;
	}


	switch(doc[0]){
		case 'S': {
            delete estat;
            estat = new SplashImage(&window, &rTexture, doc);
			++skipLines;
			break;
		}
        case 'N':
            /*//s'ha de incloure el Minigaem1.h
            Minigaem1 minigame;
            minigame.play();
            delete estat;
            estat = new Minigaem1();
            */
			break;
        case 'W':
            /*
            //buidar drawableObjects; -> IMPORTANTISSIM FER DELETE DELS PUNTERS!!!!!!!!!!!!!

            drawableObjects.push_back();
            */
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
//std::cerr << "game loop" << std::endl;
		std::ifstream estatFile;
		estatFile.open("res/documents/Status.txt");
		std::string stat;
		getline(estatFile, stat);
		if(stat == "OK") {
			//delete OK from estatFile
            if( remove( "res/documents/Status.txt" ) != 0 ) std::cout <<  "Error deleting file" << std::endl;
			readNextState(skipLines);
		}
        estatFile.close();
// std::cerr << "Estat comprobat" << std::endl;
// std::cerr << "I will processEvents" << std::endl;
		processEvents();
// std::cerr << "Events processed" << std::endl;
		timeSinceLastUpdate += clock.restart();

		while(timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
// std::cerr << "I will process events" << std::endl;
			processEvents();
// std::cerr << "event processed" << std::endl;
// std::cerr << "I will update" << std::endl;
            estat->update(TimePerFrame);
// std::cerr << "update done" << std::endl;
		}
// std::cerr << "before render" << std::endl;
        estat->render();
        estat->paint(); // AMAZING
// std::cerr << "after render" << std::endl;
	}
	return EXIT_SUCCESS;
}
