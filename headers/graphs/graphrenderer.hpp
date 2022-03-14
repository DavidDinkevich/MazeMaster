//
// Created by david on 10/6/21.
//

#ifndef MAZEMASTER_GRAPHRENDERER_HPP
#define MAZEMASTER_GRAPHRENDERER_HPP

#include <SFML/Graphics.hpp>
#include "graph.hpp"

enum PathStyle {
    DOTS, LINES
};

class GraphRenderer {
private:
    void drawLinePath(sf::RenderWindow& window,
                  const sf::Vector2f& topLeft,
                  const std::vector<std::pair<int, int>>& path) const;

    void drawDottedPath(sf::RenderWindow& window,
                      const sf::Vector2f& topLeft,
                      const std::vector<std::pair<int, int>>& path) const;
protected:
    const Graph *graph;
    float cellW;
    float cellH;
    PathStyle pathStyle;
public:
    GraphRenderer(const Graph *graph, float cellW, float cellH);

    virtual void drawGraph(sf::RenderWindow &window, const sf::Vector2f& topLeft) const = 0;
    void drawPath(
            sf::RenderWindow& window,
            const sf::Vector2f& topLeft,
            const std::vector<std::pair<int, int>>& path) const;
    void setPathStyle(PathStyle style) {
        this->pathStyle = style;
    }
    PathStyle getPathStyle() const {
        return pathStyle;
    }
};


#endif //MAZEMASTER_GRAPHRENDERER_HPP
