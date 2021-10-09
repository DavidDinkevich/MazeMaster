//
// Created by david on 10/3/21.
//

#ifndef MAZEMASTER_STARTUPWINDOW_HPP
#define MAZEMASTER_STARTUPWINDOW_HPP

#include <SFML/Graphics.hpp>
#include "button.hpp"

class StartupWindow {
private:
    sf::RenderWindow window;
    Button mazeButton;
    Button obstacleGraphButton;
private:
    void handleInput();
    void draw();
public:
    StartupWindow(const sf::Font& defFont);
    void run();
};


#endif //MAZEMASTER_STARTUPWINDOW_HPP
