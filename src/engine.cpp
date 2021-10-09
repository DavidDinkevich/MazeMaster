//
// Created by david on 9/30/21.
//

#include "../headers/engine.hpp"
#include <iostream>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>
#include "gui/startupwindow.hpp"

using namespace sf;
using namespace std;

Engine::Engine(const sf::Vector2f& size, int fps)
: size(size), fps(fps) {
    // Create window
//    window.create(sf::VideoMode(size.x, size.y),
//                  "MazeGraph Master", sf::Style::Default);
    window.setFramerateLimit(fps);


    // LOAD FONT
    if (!Engine::arial.loadFromFile("resources/arial.ttf")) {
        cout << "ERROR\n";
    }


}

void Engine::run() {
//    StartupWindow startupWindow(arial);
//    startupWindow.run();



//     Main loop - Runs until the window is closed
//    while (window.isOpen()) {
//        input();
//        draw();
//    }
}

void Engine::input() {
    Event event;

    while (window.pollEvent(event)) {
        // Window closed
        if (event.type == Event::Closed) {
            window.close();
        }

        // Handle Keyboard Input
        if (event.type == Event::KeyPressed) {
            // Quit
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
            }
        }
    }

}

void Engine::draw() {
    window.clear({237,227,209});
    RectangleShape line({2, (float) window.getSize().y});
    line.setPosition(200, 0);
    window.draw(line);
    window.display();
}
