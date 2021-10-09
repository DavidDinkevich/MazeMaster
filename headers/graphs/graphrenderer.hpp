//
// Created by david on 10/6/21.
//

#ifndef MAZEMASTER_GRAPHRENDERER_HPP
#define MAZEMASTER_GRAPHRENDERER_HPP

#include <SFML/Graphics.hpp>
#include "graph.hpp"

class GraphRenderer {
protected:
    const Graph *graph;
    float cellW;
    float cellH;
public:
    GraphRenderer(const Graph *graph, float cellW, float cellH);

    virtual void drawGraph(sf::RenderWindow &window, const sf::Vector2f& topLeft) const = 0;
    void drawPath(
            sf::RenderWindow& window,
            const sf::Vector2f& topLeft,
            const std::vector<std::pair<int, int>>& path) const;
};


#endif //MAZEMASTER_GRAPHRENDERER_HPP
