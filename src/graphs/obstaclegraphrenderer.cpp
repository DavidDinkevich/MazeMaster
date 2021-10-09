//
// Created by david on 10/5/21.
//

#include "graphs/obstaclegraphrenderer.hpp"

using namespace std;
using namespace sf;

ObstacleGraphRenderer::ObstacleGraphRenderer(const Graph *graph, float cellW, float cellH)
: GraphRenderer(graph, cellW, cellH) {
}

void ObstacleGraphRenderer::drawGraph(RenderWindow &window, const Vector2f &topLeft) const {
    // graph pointer guaranteed to be ObstacleGraph. If graph == nullptr, you shouldn't
    // be calling this function anyway and you'll crash
    ObstacleGraph *obstacleGraph = (ObstacleGraph *) graph;
    // Randomize rng
    srand(time(NULL) + rand() % 10000);
    const bool *cells = obstacleGraph->getCells();
    // Draw black cells for obstacles
    for (int r = 0; r < obstacleGraph->getNumRows(); r++) {
        for (int c = 0; c < obstacleGraph->getNumCols(); c++) {
            int cellVal = cells[r * obstacleGraph->getNumCols() + c];
            // Only draw closed cells
            if (!cellVal)
                continue;
            RectangleShape cell({cellW, cellH});
            cell.setPosition(topLeft.x + c * cellW, topLeft.y + r * cellH);
            cell.setFillColor(Color::Black);
            window.draw(cell);
        }
    }
}

//void ObstacleGraphRenderer::setGraph(const ObstacleGraph *graph) {
//    this->graph = graph;
//}
