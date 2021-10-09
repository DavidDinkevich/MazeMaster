//
// Created by david on 10/3/21.
//

#include "gui/startupwindow.hpp"

using namespace sf;
using namespace std;

StartupWindow::StartupWindow(const Font& font)
: mazeButton({}, Color::White, Color::Black), obstacleGraphButton({}, Color::White, Color::Black) {
    // Create window
    window.create(sf::VideoMode(450, 350),
                  "MazeGraph Master", sf::Style::Default);
    window.setFramerateLimit(60);
    // Create obstacle graph button
    obstacleGraphButton.setFont(font);
    obstacleGraphButton.setText("Make Obstacle graph");
    obstacleGraphButton.setPosition({
        window.getSize().x / 2 - obstacleGraphButton.getSize().x / 2,
        ((float)window.getSize().y) / 1.4f});
    // Create maze button
    mazeButton.setFont(font);
    mazeButton.setText("Generate MazeGraph");
    mazeButton.setSize(obstacleGraphButton.getSize());
    mazeButton.setPosition({
       window.getSize().x / 2 - obstacleGraphButton.getSize().x / 2,
       ((float)window.getSize().y) / 2 + obstacleGraphButton.getSize().y * 0.8f});
    mazeButton.setTextPosition({
       mazeButton.getPosition().x + mazeButton.getSize().x / 4,
       mazeButton.getPosition().y + mazeButton.getSize().y / 10});

    // Same size as other button
//    mazeButton.setAction([&]() {
//        MainWindow mazeWindow({800, 600}, 60, font);
//        mazeWindow.run();
//    });

}

void StartupWindow::run() {
    while (window.isOpen()) {
        handleInput();
        draw();
    }
}

void StartupWindow::handleInput() {
    Event event;
    Button* buttons[] = { &mazeButton, &obstacleGraphButton };

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
        // Check each button for click events
        Vector2i mouseCoords = Mouse::getPosition(window);
        for (auto buttonPtr : buttons) {
            if (event.type == Event::MouseButtonPressed) {
                if (buttonPtr->containsPoint({(float)mouseCoords.x, (float)mouseCoords.y})) {
                    buttonPtr->setButtonState(Button::PRESSED);
                    buttonPtr->getAction()();
                    break;
                }
            }
            if (event.type == Event::MouseButtonReleased) {
                buttonPtr->setButtonState(Button::DEFAULT);
            }
        }
    }
}

void StartupWindow::draw() {
    window.clear({237,227,209});
    window.draw(mazeButton);
    window.draw(obstacleGraphButton);
    window.display();

}
