//
// Created by david on 10/3/21.
//

#include "gui/mainwindow.hpp"
#include "graphs/obstaclegraph.hpp"
#include "graphs/obstaclegraphrenderer.hpp"

using namespace sf;
using namespace std;

float MainWindow::getGraphCellWidth() {
    return (window.getSize().x - controlPanelWidth - 2.0f * graphPadding) / graphWidth;
}

float MainWindow::getGraphCellHeight() {
    return (window.getSize().y - 2.0f * graphPadding) / graphHeight;
}

MainWindow::MainWindow(int fps, const sf::Font &defFont) : controlPanelWidth(200.0f) {
    window.create(VideoMode(800, 600), "MazeGraph Master", Style::Default);
    window.setFramerateLimit(fps);

    // SIZE OF GRAPH
    graphWidth = 48 / 2;
    graphHeight = 48 / 2;
    graphPadding = 10.0f;

    // CREATE BUTTONS

    Vector2f buttonSize(controlPanelWidth * 0.9f, 50);
    float buttonX = (controlPanelWidth - buttonSize.x) / 2.0f;
    float buttonH = 33.0f;
    float buttonGap = 10.0f;
    // Generate MazeGraph button
    genMazeButton = make_unique<Button>(Vector2f (), Color::White, Color::Black);
    genMazeButton->setFont(defFont);
    genMazeButton->setText("Generate Maze");
    genMazeButton->setSize({buttonSize.x, genMazeButton->getSize().y});
    genMazeButton->setPosition({buttonX, buttonH});
    // Solve MazeGraph With A* button
    solveWithAStarButton = make_unique<Button>(Vector2f(), Color::White, Color::Black);
    solveWithAStarButton->setFont(defFont);
    solveWithAStarButton->setText("Solve with A*");
    solveWithAStarButton->setSize({buttonSize.x, solveWithAStarButton->getSize().y});
    solveWithAStarButton->setPosition({buttonX, 5 * buttonH + buttonGap});
    // Generate Custom Map button
    genObstacleMapButton = make_unique<Button>(Vector2f(), Color::White, Color::Black);
    genObstacleMapButton->setFont(defFont);
    genObstacleMapButton->setText("Custom Map");
    genObstacleMapButton->setSize({buttonSize.x, solveWithAStarButton->getSize().y});
    genObstacleMapButton->setPosition({buttonX, 2 * buttonH + buttonGap});

    // BUTTON ACTIONS

    // On click: generates a new maze
    genMazeButton->setAction([&]() {
        if (programState != MAZE_MODE) {
            programState = MAZE_MODE;
            // Create maze
            currGraph.reset(new MazeGraph(graphWidth, graphHeight));
            // Reset graph solver
            solver.reset(new AStarSolver(currGraph.get()));
            // Initial dest is top left, so solver won't immediately start solving
            solver->setDest(make_pair(0, 0));
            // Set maze renderer
            graphRenderer.reset(
                    new MazeRenderer(currGraph.get(), getGraphCellWidth(), getGraphCellHeight()));
        }
        // Clear solver
        solver->clearData();
        // Random populate graph
        currGraph->randomPopulate();
    });

    // On click: generates a new obstacle graph
    genObstacleMapButton->setAction([&]() {
        if (programState != OBSTACLE_MAP_MODE) {
            programState = OBSTACLE_MAP_MODE;
            // Create obstacle map
            currGraph.reset(new ObstacleGraph(graphWidth, graphHeight));
            // Reset graph solver
            solver.reset(new AStarSolver(currGraph.get()));
            // Create graph renderer
            graphRenderer = make_unique<ObstacleGraphRenderer>(
                    currGraph.get(), getGraphCellWidth(), getGraphCellHeight());
        }
        // Clear solver
        solver->clearData();
        // Random populate graph
        currGraph->randomPopulate();
    });
    // On click: if current graph is a maze, directs the AStarSolver to begin
    // solving the maze
    solveWithAStarButton->setAction([&]() {
        if (programState == MAZE_MODE) {
            solver->clearData(); // Clear solver to prepare for new graph
            // Set destination bottom right corner, solver will start to search for it
            solver->setDest(make_pair(graphWidth - 1, graphHeight - 1));
        }
    });

}

void MainWindow::run() {
    while (window.isOpen()) {
        handleInput();
        draw();
        update();
    }
}

void MainWindow::handleInput() {
    Event event{};
    // Array of the buttons to easily check if one has been clicked
    Button* buttons[] = {
            genMazeButton.get(), genObstacleMapButton.get(), solveWithAStarButton.get()
    };
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
        if (event.type == Event::MouseButtonPressed) {
            Vector2i mouseCoords = Mouse::getPosition(window);
//            cout << mouseCoords.x << ", " << mouseCoords.y << endl;
            // Check if one of the buttons was clicked
            for (auto buttonPtr : buttons) {
                if (buttonPtr->containsPoint({(float)mouseCoords.x, (float)mouseCoords.y})) {
                    // Tell button it's been clicked
                    buttonPtr->setButtonState(Button::PRESSED);
                    buttonPtr->getAction()(); // Execute button action
                    break; // No need to proceed, can only click one button at a time...
                }
            }
        }
        if (event.type == Event::MouseButtonReleased) {
            // Release all buttons (if button wasn't clicked, nothing happens)
            for (auto buttonPtr: buttons) {
                buttonPtr->setButtonState(Button::DEFAULT);
            }
        }
        if (event.type == Event::MouseMoved &&
            programState == OBSTACLE_MAP_MODE &&
            (Mouse::isButtonPressed(Mouse::Left) || Mouse::isButtonPressed(Mouse::Right)))
        {
            ObstacleGraph *obstacleGraph = (ObstacleGraph *) currGraph.get();
            Vector2i mouseCoords = Mouse::getPosition(window);
            int r = (mouseCoords.y - graphPadding) / getGraphCellHeight();
            int c = (mouseCoords.x - controlPanelWidth - graphPadding) / getGraphCellWidth();
            if (r >= 0 && r < obstacleGraph->getNumRows() &&
                c >= 0 && c < obstacleGraph->getNumCols())
            {
                obstacleGraph->setCell(make_pair(r, c), Mouse::isButtonPressed(Mouse::Left));
                solver->clearData();
            }

        }
    }
}

void MainWindow::draw() {
    // Clear previous frame
    window.clear(Color::White);

    // DRAW CONTROL PANEL

    RectangleShape controlPanelBackground({200, (float) window.getSize().y});
    controlPanelBackground.setFillColor({237,227,209});
    window.draw(controlPanelBackground);
    // Draw buttons
    window.draw(*genMazeButton);
    window.draw(*genObstacleMapButton);


    // DRAW MAZE/OBSTACLE MAP

    switch (programState) {
        case DEFAULT_MODE: {
            RectangleShape back({
                window.getSize().x - controlPanelWidth, (float) window.getSize().y});
            back.setPosition(controlPanelWidth, 0);
            back.setFillColor(Color::White);
            window.draw(back);
            break;
        }
        case MAZE_MODE: {
            // Draw "solve" button
            window.draw(*solveWithAStarButton);
        }
        case OBSTACLE_MAP_MODE: {
            // Draw Graph
            graphRenderer->drawGraph(
                    window, Vector2f(controlPanelWidth + graphPadding, graphPadding));
            graphRenderer->drawPath(
                    window,
                    Vector2f(controlPanelWidth + graphPadding, graphPadding),
                    solver->getCurrentSolutionPath());
            break;
        }
    }
    // Display the window
    window.display();
}

void MainWindow::update() {
    if (programState != DEFAULT_MODE) {
        solver->doOneIteration();
    }
}