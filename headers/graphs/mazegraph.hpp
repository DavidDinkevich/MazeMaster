//
// Created by david on 10/1/21.
//

#ifndef MAZEMASTER_MAZEGRAPH_HPP
#define MAZEMASTER_MAZEGRAPH_HPP

#include "gridgraph.hpp"
#include <vector>


class MazeGraph : public GridGraph<int> {
public:
    MazeGraph(int numRows, int numCols);

    void randomPopulate() override;
    bool cellsAreConnected(
            const std::pair<int, int>& n1, const std::pair<int, int>& n2) const override;
    std::vector<std::pair<int, int>> solveWithAStar() const;
};

#endif //MAZEMASTER_MAZEGRAPH_HPP
