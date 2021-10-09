//
// Created by david on 10/6/21.
//

#include "graphs/graphrenderer.hpp"
#import <iostream>
#include <cmath>

using namespace sf;
using namespace std;



GraphRenderer::GraphRenderer(const Graph *graph, float cellW, float cellH)
: graph(graph), cellW(cellW), cellH(cellH) {
}

void GraphRenderer::drawPath(RenderWindow &window, const Vector2f &topLeft,
                             const vector<pair<int, int>>& path) const {
//    pair<int, int> start = make_pair(0, 0);
//    pair<int, int> dest = make_pair(maze->getNumRows() - 1, maze->getNumCols() - 1);
//    vector<pair<int, int>> path = AStarSolver::solve(*maze, start, dest);
    float lineThickness = 4.0f;

    for (int i = 0; path.size() >= 2 && i < path.size() - 1; i++) {
        CircleShape c(lineThickness);
        c.setFillColor(Color::Magenta);
        c.setPosition(
                topLeft.x + path[i].second * cellW + cellW / 2.0f - c.getRadius() / 2,
                topLeft.y + path[i].first * cellH + cellH / 2.0f - c.getRadius() / 2);
        window.draw(c);
//        RectangleShape c({cellW, cellH});
//        c.setFillColor(Color::Magenta);
//        c.setPosition(
//                topLeft.x + path[i].second * cellW + cellW / 2.0f - c.getSize().x / 2,
//                topLeft.y + path[i].first * cellH + cellH / 2.0f - c.getSize().y / 2);
//        window.draw(c);


//        RectangleShape line;
//        line.setPosition(
//                topLeft.x + path[i].second * cellW + cellW / 2.0f,
//                topLeft.y + path[i].first * cellH + cellH / 2.0f);
//
////        line.setOutlineColor(Color::Blue);
////        line.setOutlineThickness(1.0f);
//        // Determine type of line to draw: vertical/horizontal/diagonal
//        int dirR = path[i + 1].first - path[i].first;
//        int dirC = path[i + 1].second - path[i].second;
////
//        // Horizontal lines
//        if (dirR == 0) {
////              line.setPosition(
////                    topLeft.x + path[i].second * cellW + cellW / 2.0f,
////                    topLeft.y + path[i].first * cellH + cellH / 2.0f);
//            line.setSize(Vector2f(
//                    // dirC > 0 indicates that we're drawing from left to right
//                    // If drawing from right to left, add lineThickness to the width to avoid
//                    // a gap at the end of the line
//                    dirC * cellW + (dirC > 0 ? lineThickness : 0.0f),
//                    lineThickness));
//        }
//        else if (dirC == 0) { // Vertical lines
//            // If drawing north to south, add lineThickness to the height to avoid
//            // a gap at the end of the line
//            line.setSize(Vector2f(
//                    lineThickness,
//                    // dirR > 0 indicates that we're drawing north-south
//                    dirR * cellH + (dirR > 0 ? lineThickness : 0.0f)));
//        }
//        // Diagonal lines
//        else if (abs(dirC) + abs(dirR) == 2) {
//
//            // Determine angle of line
//            float angle;
//            if (dirR * dirC > 0)
//                angle = 45.0f * (dirR < 0 ? 3.0f : 7.0f);
//            else
//                angle = 45.0f * (dirR < 0 ? 1.0f : 5.0f);
//
//            // Determine size
//            line.setSize({cellW * 1.4142f, lineThickness});
//            line.setPosition(line.getPosition().x + lineThickness / 2, line.getPosition().y + lineThickness/ 2);
////            line.setPosition(line.getPosition().x + lineThickness
////                             - (angle > 270 ? (lineThickness / (2 *1.414) ) :0), line.getPosition().y + (angle > 270 ? (lineThickness / (2*1.414)) : 0));
//
//
//            line.setRotation(-angle);
//        }
//
//        line.setFillColor(Color::Magenta);
//        window.draw(line);
    }

}
