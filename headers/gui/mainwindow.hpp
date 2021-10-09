//
// Created by david on 10/3/21.
//

#ifndef MAZEMASTER_MAINWINDOW_HPP
#define MAZEMASTER_MAINWINDOW_HPP
//
// Created by david on 10/3/21.
//

#include <SFML/Graphics.hpp>
#include <memory>
#include "button.hpp"
#include "graphs/mazegraph.hpp"
#include "graphs/mazerenderer.hpp"
#include "graphs/astarsolver.hpp"
#include "graphs/graphrenderer.hpp"

class MainWindow {
private:
    sf::RenderWindow window;

// CONTROL PANEL
    float controlPanelWidth;

// BUTTONS
    std::unique_ptr<Button> genMazeButton;
    std::unique_ptr<Button> genObstacleMapButton;
    std::unique_ptr<Button> solveWithAStarButton;

// GRAPHS
    int programState = DEFAULT_MODE;
    std::unique_ptr<Graph> currGraph;
    float graphPadding;
    int graphWidth;
    int graphHeight;
    std::unique_ptr<GraphRenderer> graphRenderer;
    std::unique_ptr<AStarSolver> solver;

private:
    enum {
        DEFAULT_MODE,
        MAZE_MODE,
        OBSTACLE_MAP_MODE
    };

    void handleInput();
    void draw();
    void update();
    float getGraphCellWidth();
    float getGraphCellHeight();
public:
    MainWindow(int fps, const sf::Font& defFont);
    void run();
};

#endif //MAZEMASTER_MAINWINDOW_HPP
