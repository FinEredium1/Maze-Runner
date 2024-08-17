#ifndef MAZE_H
#define MAZE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

class maze
{
private:
    sf::RectangleShape _rect;
    int _width = 15;
    int _height = 15;
    int _x;
    int _y;
    sf::Color _color;

public:
    void set_color(char);
    void set_postion(int, int);
    void set_matrix(char** m);
    void draw_rect(sf::RenderWindow&);

};

#endif