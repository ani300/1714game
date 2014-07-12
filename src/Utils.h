#ifndef AUX
#define AUX

#include <map>
#include <cstdio>
#include <string>
#include <memory>
#include <vector>
#include <cassert>
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>
#include <functional>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace std;

enum directions {
    dir_up, dir_down, dir_right, dir_left, dir_up_right, dir_down_left, dir_up_left, dir_down_right, dir_none
};

enum mouseButtons {
    mouse_left, mouse_right, mouse_rodeta, mouse_none
};

/*int inverseDir(directions dir){
    if(dir == dir_none) return dir_none;
    if(dir%2 == 0) return dir+1;
    else return dir-1;
}*/

//                      N   S   E   W    NE     SW    NW   SE  NONE
const float dirx[9] = { 0,  0,  1, -1,  0.5,  -0.5, -0.5, 0.5,   0};
const float diry[9] = {-1,  1,  0,  0, -0.5,   0.5, -0.5, 0.5,   0};

const float PlayerSpeed = 500.f;
const sf::Time TimePerFrame = sf::seconds(1.f/60.f); // 60 fps

const sf::Vector2u gameSize(1920,1080);

#endif
