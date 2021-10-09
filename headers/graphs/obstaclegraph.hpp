//
// Created by david on 10/5/21.
//

#ifndef MAZEMASTER_OBSTACLEGRAPH_HPP
#define MAZEMASTER_OBSTACLEGRAPH_HPP

#include "graphs/gridgraph.hpp"

class ObstacleGraph : public GridGraph<bool> {
public:
    ObstacleGraph(int numRows, int numCols);
    void randomPopulate() override;
    std::vector<std::pair<int, int>> getNeighbors(const std::pair<int, int>& loc) const override;
    bool cellsAreConnected(
            const std::pair<int, int>& n1, const std::pair<int, int>& n2) const override;
};

#endif //MAZEMASTER_OBSTACLEGRAPH_HPP
