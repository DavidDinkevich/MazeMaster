//
// Created by david on 10/5/21.
//

#ifndef MAZEMASTER_GRAPH_HPP
#define MAZEMASTER_GRAPH_HPP

#include <vector>

class Graph {
public:
    enum {
        NORTH = 0b00001,
        EAST = 0b00010,
        SOUTH = 0b00100,
        WEST = 0b01000,
        VISITED = 0b10000
    };

    /**
     * Randomly populate the graph.
     */
    virtual void randomPopulate() = 0;
    /**
     * Returns a vector of the neighbors of the given cell. By default, these are
     * the cell's northern, eastern, southern, and western neighbors.
     */
    virtual std::vector<std::pair<int, int>> getNeighbors(
            const std::pair<int, int>& loc) const = 0;
    /**
     * Get the distance between two cells in the grid. Treats each cell as a 1x1 block and
     * returns the Euclidean distance between their centers.
     */
    virtual float getDistanceBetween(
            const std::pair<int, int>& n1, const std::pair<int, int>& n2) const = 0;

    /**
     * Returns true if the two cells are connected (by default, if one is the
     * northern/eastern/southern/western neighbor of the other).
     */
    virtual bool cellsAreConnected(const std::pair<int, int>& n1,
                                   const std::pair<int, int>& n2) const = 0;

    virtual int getNumRows() const = 0;
    virtual int getNumCols() const = 0;
};


#endif //MAZEMASTER_GRAPH_HPP
