//
// Created by david on 10/5/21.
//

#ifndef MAZEMASTER_OBSTACLEGRAPHRENDERER_HPP
#define MAZEMASTER_OBSTACLEGRAPHRENDERER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "obstaclegraph.hpp"
#include "graphrenderer.hpp"

class ObstacleGraphRenderer : public GraphRenderer {
public:
    ObstacleGraphRenderer(const Graph *graph, float cellW, float cellH);

    void drawGraph(sf::RenderWindow &window, const sf::Vector2f &topLeft) const override;

//    void setGraph(const ObstacleGraph *graph);
};


#endif //MAZEMASTER_OBSTACLEGRAPHRENDERER_HPP
