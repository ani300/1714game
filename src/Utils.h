#ifndef AUX
#define AUX

enum directions {
	up, down, left, right, none;
};

enum mouseButtons {
	left, right, rodeta, none;
};

//            		  N   S   E   W
const int dirx[4] = { 0,  0,  1, -1};
const int diry[4] = {-1,  1,  0,  0};

const float Joc::PlayerSpeed = 500.f;
const sf::Time Joc::TimePerFrame = sf::seconds(1.f/60.f); // 60 fps

#endif