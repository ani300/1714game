#include "Joc.h"

const float Joc::PlayerSpeed = 500.f;
const sf::Time Joc::TimePerFrame = sf::seconds(1.f/60.f); // 60 fps

//Constructor
Joc::Joc() : window(sf::VideoMode::getDesktopMode() , L"1714: La resistència de l'Història"
	, sf::Style::Resize|sf::Style::Close)
	, graphic(window)
	, mPlayer()
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingLeft(false)
	, mIsMovingRight(false) {
		mPlayer.setRadius(40.f);
		mPlayer.setPosition(100.f,100.f);
		mPlayer.setFillColor(sf::Color::Yellow);    
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
			case sf::Event::Closed:
				window.close();
				break;
		}
	}
}

void Joc::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
	if (key == sf::Keyboard::W) mIsMovingUp = isPressed;
	if (key == sf::Keyboard::S) mIsMovingDown = isPressed;
	if (key == sf::Keyboard::A) mIsMovingLeft = isPressed;
	if (key == sf::Keyboard::D) mIsMovingRight = isPressed;
}

void Joc::update(sf::Time elapsedTime) {
	sf::Vector2f movement(0.f,0.f);
	if (mIsMovingUp) movement.y -= PlayerSpeed;
	if (mIsMovingDown) movement.y += PlayerSpeed;
	if (mIsMovingLeft) movement.x -= PlayerSpeed;
	if (mIsMovingRight) movement.x += PlayerSpeed;
	mPlayer.move(movement * elapsedTime.asSeconds());
}

void Joc::render() {
	window.clear();
	window.draw(mPlayer);
	window.display();
}

int Joc::play() {
	
	//Joc LOOP
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while(window.isOpen()) {
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
