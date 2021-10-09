//
// Created by david on 10/1/21.
//

#ifndef MAZEMASTER_MAZERENDERER_HPP
#define MAZEMASTER_MAZERENDERER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "mazegraph.hpp"
#include "graphrenderer.hpp"

class MazeRenderer : public GraphRenderer {
public:
    MazeRenderer(const Graph *graph, float cellW, float cellH);

    void drawGraph(sf::RenderWindow &window, const sf::Vector2f& topLeft) const override;
//    void setGraph(const MazeGraph *mazeGraph);
};

#endif //MAZEMASTER_MAZERENDERER_HPP
