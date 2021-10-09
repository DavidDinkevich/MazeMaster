//
// Created by david on 10/1/21.
//

#include "graphs/mazegraph.hpp"
#include <stack>

using namespace std;


MazeGraph::MazeGraph(int numRows, int numCols) : GridGraph<int>(numRows, numCols) {
}

void MazeGraph::randomPopulate() {
    // Clear maze
    setAllCells(0);
    // Calibrate rng
    srand(time(NULL) + rand() % 10000);
    stack<pair<int, int>> stack;
    auto startPos = make_pair(0, 0);
    stack.push(startPos);

    while (stack.size() > 0) {
        // Get current cell
        pair<int, int> top = stack.top();
        int topIndex = top.first * getNumCols() + top.second;
        // Mark current cell as visited
        cells[topIndex] |= VISITED;
        // Get neighbors
        vector<pair<int, int>> neighbors = getNeighbors(top);
        // Remove all neighbors that are already visited
        auto unvisitedEnd = remove_if(neighbors.begin(), neighbors.end(), [&](const auto& item) {
            return cells[item.first * getNumCols() + item.second] & VISITED;
        });
        neighbors.erase(unvisitedEnd, neighbors.end()); // Erase all already visited neighbors
        // Move to next neighbor (if there is one)
        if (neighbors.empty()) {
            stack.pop();
        } else {
            // Choose neighbor randomly
            int dest = rand() % neighbors.size();
            // Helper function to connect two nodes together
            auto connectNodes = [&](int n1, int n2, int dir1, int dir2) {
                cells[n1] |= dir1;
                cells[n2] |= dir2;
            };
            // Get index of the neighbor in the cell array
            int destCellIndex = neighbors[dest].first * getNumCols() + neighbors[dest].second;
            if (top.first > neighbors[dest].first) // Northern neighbor
                connectNodes(topIndex, destCellIndex, NORTH, SOUTH);
            else if (top.first < neighbors[dest].first) // Southern neighbor
                connectNodes(topIndex, destCellIndex, SOUTH, NORTH);
            else if (top.second < neighbors[dest].second) // Eastern neighbor
                connectNodes(topIndex, destCellIndex, EAST, WEST);
            else // Western neighbor
                connectNodes(topIndex, destCellIndex, WEST, EAST);

            // Push new node to stack
            stack.push(neighbors[dest]);
        }
    }
    // Open start and destination nodes
    cells[0] |= WEST;
    cells[getNumRows() * getNumCols() - 1] |= EAST;


//    for (int i = 0; i < getNumRows() * getNumCols(); i++) {
//        cells[i] = NORTH | EAST | SOUTH | WEST;
//    }
}

bool MazeGraph::cellsAreConnected(const pair<int, int>& n1, const pair<int, int>& n2) const {
    if (!GridGraph<int>::cellsAreConnected(n1, n2))
        return false;
    // Get indices of nodes in cells array
    int n1Index = n1.first * getNumCols() + n1.second;
    int n2Index = n2.first * getNumCols() + n2.second;
    // Difference in row and col
    int dr = n1.first - n2.first;
    int dc = n1.second - n2.second;
    if (dr == 1) // node1 is below node2
        return (cells[n1Index] & NORTH) != 0 && (cells[n2Index] & SOUTH) != 0;
    if (dr == -1) // node1 is above node2
        return (cells[n1Index] & SOUTH) != 0 && (cells[n2Index] & NORTH) != 0;
    if (dc == 1) // node1 is to the right of node2
        return (cells[n1Index] & WEST) != 0 && (cells[n2Index] & EAST) != 0;
    // node1 is to the left of node2
    return (cells[n1Index] & EAST) != 0 && (cells[n2Index] & WEST) != 0;
}

vector<pair<int, int>> MazeGraph::solveWithAStar() const {
    vector<pair<int, int>> v;
    return v;
}

