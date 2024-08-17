#include "maze.h"
#include <iostream>
using namespace std;
using namespace sf;

void maze::set_postion(int x_factor, int y_factor){
    _x = x_factor;
    _y = y_factor;
}

void maze::set_color(char c){
    if (c == 'S'){
        _color = sf::Color::Green;
    }
    else if (c == 'E'){
        _color = sf::Color::Red;
    }
    else if (c == '#'){
        _color = sf::Color::Black;
    }
    else if (c == 'V'){
        _color = sf::Color::Magenta;
    }
    else{
        _color = sf::Color::White;
    }
}

void maze::draw_rect(RenderWindow& win){
    _rect.setSize(sf::Vector2f(_width, _height));
    _rect.setFillColor(_color);
    _rect.setPosition(_x, _y);
    win.draw(_rect);
}


