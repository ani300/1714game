#ifndef AUX
#define AUX

#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

enum directions {
    dir_up, dir_down, dir_left, dir_right, dir_up_right, dir_up_left, dir_down_right, dir_down_left, dir_none
};

enum mouseButtons {
    mouse_left, mouse_right, mouse_rodeta, mouse_none
};

//            		  N   S   E   W  NE  NW SE  SW NONE          
const int dirx[9] = { 0,  0,  1, -1,  1, -1, 1, -1, 0};
const int diry[9] = {-1,  1,  0,  0, -1, -1, 1,  1, 0};

const float PlayerSpeed = 500.f;
const sf::Time TimePerFrame = sf::seconds(1.f/60.f); // 60 fps

#endif
