#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "maze.h"
using namespace sf;

#include <iostream>
using namespace std;

vector<pair<int, int>> get_neighbours(int x, int y, int rows, int columns, char** _matrix){
    vector<pair<int, int>> neighbor_vec;
    if (x > 0 && _matrix[x-1][y] != '#' && _matrix[x-1][y] != 'V'){
        neighbor_vec.push_back({x-1, y});
    }

    if (y > 0 && _matrix[x][y-1] != '#' && _matrix[x][y-1] != 'V'){
        neighbor_vec.push_back({x, y-1});
    }

    if (x+1 < rows && _matrix[x+1][y] != '#' && _matrix[x+1][y] != 'V'){
        neighbor_vec.push_back({x+1, y});
    }

    if (y+1 < columns && _matrix[x][y+1] != '#' && _matrix[x][y+1] != 'V'){
        neighbor_vec.push_back({x, y+1});
    }


    return neighbor_vec;
}


int main(int argc, char* argv[])
{
    maze m1;
    pair<int,int> start_pos;

    string s1;
    int n;
    bool dfs = false;
    bool bfs = false;
    cout << "Which searching algorithm would you like to choose? {bfs} {dfs}: ";
    cin >> s1;
    if (s1 == "dfs"){
        dfs = true;
    }
    else if (s1 == "bfs"){
        bfs = true;
    }

    cout << "Choose speed in millisecond: ";
    cin >> n;


    string filename;
    if (argc > 1){
        filename = "data/" + string(argv[1]);
    }
    else{
        cout << "Input File path "; 
        cin >> filename;
    }


    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    int row, col;
    file >> row >> col;
    int screenWidth = 15;
    int screenHeight = 15;
    RenderWindow window(VideoMode(screenWidth * col, screenHeight * row), "MAZE");
    window.setFramerateLimit(60);

    char** maze_arr = new char*[row];

    for (int i = 0; i < row; ++i) {
        maze_arr[i] = new char[col];
    }

    char holder;

    for (int i(0); i < row; i++){
        for (int j(0); j < col; j++){
            file >> holder;
            maze_arr[i][j] = holder;
        }
    }

    for (int i(0); i < row; i++){
        for (int j(0); j < col; j++){
            if (maze_arr[i][j] == 'S'){
                start_pos.first = i;
                start_pos.second = j;
            }
        }
    }

    queue<pair<int, int>> q;
    q.push(start_pos);

    stack<pair<int, int>> st;
    st.push(start_pos);
    vector<pair<int, int>> neigh_vec;

    Event event;

    //int i1 = 0;
    //int j1 = 0;
    while (window.isOpen())
    {

        window.clear();

        for (int i(0); i < row; i++) {
            for (int j(0); j < col; j++) {
                m1.set_color(maze_arr[i][j]);
                m1.set_postion(15*j, 15*i);
                m1.draw_rect(window);
            }
        }

        if (bfs && !q.empty()){
            pair<int, int> cur = q.front();
            if (maze_arr[cur.first][cur.second] != 'S' && maze_arr[cur.first][cur.second] != 'E') {
                maze_arr[cur.first][cur.second] = 'V';
            }
            if (maze_arr[cur.first][cur.second] == 'E') {
                bfs = false;
            }
            if (bfs){
                q.pop();
                neigh_vec = get_neighbours(cur.first, cur.second, row, col, maze_arr);

                for (auto neighbor : neigh_vec) {
                    if (maze_arr[neighbor.first][neighbor.second] == '.' || maze_arr[neighbor.first][neighbor.second] == 'E') {
                        q.push(neighbor);

                    }
                }
            }
            
        }

        if (dfs && !st.empty()) {
            pair<int, int> cur = st.top();
            if (maze_arr[cur.first][cur.second] != 'S' && maze_arr[cur.first][cur.second] != 'E') {
                maze_arr[cur.first][cur.second] = 'V';
            }

            if (maze_arr[cur.first][cur.second] == 'E') {
                dfs = false;
            }

            if (dfs) {
                st.pop();
                neigh_vec = get_neighbours(cur.first, cur.second, row, col, maze_arr);
                for (auto neighbor : neigh_vec) {
                    if (maze_arr[neighbor.first][neighbor.second] == '.' || maze_arr[neighbor.first][neighbor.second] == 'E') {
                        st.push(neighbor);
                    }
                }
            }
        }





        window.display();

        sf::sleep(milliseconds(n));


        while (window.pollEvent(event))
        {

            if (event.type == Event::Closed)
            {

                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                }
            }
        }
    
    }

    for (int i = 0; i < row; ++i) {
        delete[] maze_arr[i];
    }
    delete[] maze_arr;

    return 0;
}
