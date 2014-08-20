#include "Controller.h"
/*  THE MOST USEFUL CLASS IN THE GAME
struct AircraftMover {
	AircraftMover(float vx, float vy)
	: velocity(vx, vy) {
	}

	void operator() (Aircraft& aircraft, sf::Time) const {
		aircraft.accelerate(velocity);
	}

	sf::Vector2f velocity;
};

Controller::Controller() {
	// Set initial key bindings
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;

	// Set initial action bindings
	initializeActions();	

	// Assign all categories to player's aircraft
	FOREACH(auto& pair, mActionBinding)
		pair.second.category = Category::ControllerAircraft;
}

void Controller::handleEvent(const sf::Event& event, CommandQueue& commands) {
	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

void Controller::handleRealtimeInput(CommandQueue& commands) {
	// Traverse all assigned keys and check if they are pressed
	FOREACH(auto pair, mKeyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

void Controller::assignKey(Action action, sf::Keyboard::Key key) {
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

sf::Keyboard::Key Controller::getAssignedKey(Action action) const {
	FOREACH(auto pair, mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Controller::initializeActions() {
	const float playerSpeed = 200.f;

	mActionBinding[MoveLeft].action	 = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
	mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f));
	mActionBinding[MoveUp].action    = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
	mActionBinding[MoveDown].action  = derivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed));
}

bool Controller::isRealtimeAction(Action action) {
	switch (action)
	{
		case MoveLeft:
		case MoveRight:
		case MoveDown:
		case MoveUp:
			return true;

		default:
			return false;
	}
}
*/
