//
// Created by david on 10/1/21.
//

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "graphs/mazerenderer.hpp"
#include "graphs/graph.hpp"

using namespace sf;
using namespace std;

MazeRenderer::MazeRenderer(const Graph *graph, float cellW, float cellH)
: GraphRenderer(graph, cellW, cellH) {
}

void MazeRenderer::drawGraph(RenderWindow &window, const Vector2f& topLeft) const {
    // graph pointer guaranteed to be MazeGraph. If graph == nullptr, you shouldn't
    // be calling this function anyway and you'll crash
    MazeGraph *maze = (MazeGraph *) graph;
    const int *cells = maze->getCells();
    float lineThickness = 4.0f;

    for (int r = 0; r < maze->getNumRows(); r++) {
        for (int c = 0; c < maze->getNumCols(); c++) {
            int cellVal = cells[r * maze->getNumCols() + c];
            RectangleShape line;
            line.setFillColor(Color::Black);

            // DRAW NORTHERN BORDER (for top-row cells only)
            if (r == 0 && (cellVal & Graph::NORTH) == 0) {
                line.setPosition(topLeft.x + c * cellW, topLeft.y + r * cellH);
                line.setSize(Vector2f(cellW + lineThickness, lineThickness));
                window.draw(line);
            }
            // DRAW WESTERN BORDER (for left-most cells only)
            if (c == 0 && (cellVal & Graph::WEST) == 0) {
                line.setPosition(topLeft.x + c * cellW, topLeft.y + r * cellH);
                line.setSize(Vector2f(lineThickness, cellH));
                window.draw(line);
            }
            // DRAW EASTERN BORDER
            if ((cellVal & Graph::EAST) == 0) {
                line.setPosition(topLeft.x + (c+1) * cellW, topLeft.y + r * cellH);
                line.setSize(Vector2f(lineThickness, cellH));
                window.draw(line);
            }
            // DRAW SOUTHERN BORDER (build the wall)
            if ((cellVal & Graph::SOUTH) == 0) {
                line.setPosition(topLeft.x + c * cellW, topLeft.y + (r+1) * cellH);
                line.setSize(Vector2f(cellW + lineThickness, lineThickness));
                window.draw(line);
            }
        }
    }
}

//void MazeRenderer::setGraph(const MazeGraph *mazeGraph) {
//    graph = mazeGraph;
//}
