//
// Created by david on 9/30/21.
//

#ifndef MAZEMASTER_ENGINE_HPP
#define MAZEMASTER_ENGINE_HPP

#include <SFML/Graphics.hpp>
#include "graphs/mazegraph.hpp"
#include "graphs/mazerenderer.hpp"
#include "graphs/astarsolver.hpp"
#include "gui/mainwindow.hpp"
#include "gui/button.hpp"

class Engine {
private:
    sf::Vector2f size;
    sf::RenderWindow window;
    int fps;
    sf::Font arial;
private:
    void input();
    void draw();
public:
    Engine(const sf::Vector2f& size, int fps);

    void run();

};


#endif //MAZEMASTER_ENGINE_HPP
