//
// Created by david on 9/30/21.
//

#ifndef MAZEMASTER_GRIDGRAPH_HPP
#define MAZEMASTER_GRIDGRAPH_HPP

#include <iostream>
#include <vector>
#include "graph.hpp"

template <typename T>
class GridGraph : public Graph {
protected:
    T *cells;
private:
    int numRows;
    int numCols;
public:
    GridGraph(int numRows, int numCols);
    ~GridGraph();

    void setAllCells(T val);
    void setCell(const std::pair<int, int>& loc, T val);
    const T *getCells() const;

    // OVERRIDDEN METHODS

    std::vector<std::pair<int, int>> getNeighbors(const std::pair<int, int>& loc) const override;
    float getDistanceBetween(
            const std::pair<int, int> &n1, const std::pair<int, int> &n2) const override;
    bool cellsAreConnected(
            const std::pair<int, int> &n1, const std:: pair<int, int> &n2) const override;
    int getNumRows() const override;
    int getNumCols() const override;

};

#endif //MAZEMASTER_GRIDGRAPH_HPP
