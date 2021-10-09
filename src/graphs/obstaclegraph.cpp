//
// Created by david on 10/5/21.
//

#include "graphs/obstaclegraph.hpp"

using namespace std;

ObstacleGraph::ObstacleGraph(int numRows, int numCols) : GridGraph<bool>(numRows, numCols) {
}

void ObstacleGraph::randomPopulate() {

    // Calibrate rng
    srand(time(nullptr) + rand() % 10000);
    for (int i = 0; i < this->getNumRows() * this->getNumCols(); i++) {
        cells[i] = (bool) (rand() % 4 == 0); // Random: true/false
        cells[i] = false;
    }
    cells[0] = false;
    cells[this->getNumRows() * this->getNumCols() - 1] = false;
}

vector<pair<int, int>> ObstacleGraph::getNeighbors(const pair<int, int> &loc) const {
    vector<pair<int, int>> v = GridGraph::getNeighbors(loc);
    // ADD DIAGONAL NEIGHBORS
    // North-east neighbor
    if (loc.first > 0 && loc.second < this->getNumCols() - 1)
        v.emplace_back(make_pair(loc.first - 1, loc.second + 1));
    // South-eastern neighbor
    if (loc.first < this->getNumRows() - 1 && loc.second < this->getNumCols() - 1)
        v.emplace_back(make_pair(loc.first + 1, loc.second + 1));
    // South-western neighbor
    if (loc.first < this->getNumRows() - 1 && loc.second > 0)
        v.emplace_back(make_pair(loc.first + 1, loc.second - 1));
    // North-west neighbor
    if (loc.first > 0 && loc.second > 0)
        v.emplace_back(make_pair(loc.first - 1, loc.second - 1));
    return v;
}

bool ObstacleGraph::cellsAreConnected(
        const pair<int, int> &n1, const pair<int, int> &n2) const {
    // Indices in array
    int n1Index = n1.first * this->getNumCols() + n1.second;
    int n2Index = n2.first * this->getNumCols() + n2.second;
    // If either nodes are closed, return false:
    if (cells[n1Index] || cells[n2Index])
        return false;
    // Get distance between nodes
    int dr = n1.first - n2.first;
    int dc = n1.second - n2.second;
    // If nodes are vertical/horizontal neighbors, accept
    if (GridGraph::cellsAreConnected(n1, n2))
        return true;
    // Check if nodes are NOT diagonal neighbors, reject
    if (abs(dr) + abs(dc) != 2)
        return false;
    // If nodes are diagonal neighbors, then there are exactly 2 neighbors that they
    // share in common. If at least one is open, then the nodes are not connected.
    // Get neighbors of each
    vector<pair<int, int>> n1Neighbors = getNeighbors(n1);
    vector<pair<int, int>> n2Neighbors = getNeighbors(n2);
    sort(n1Neighbors.begin(), n1Neighbors.end()); // Sort so that we can use std::set_intersection
    sort(n2Neighbors.begin(), n2Neighbors.end());
    // Get the 2 neighbors that are in common
    vector<pair<int, int>> sharedNeighbors;
    set_intersection(n1Neighbors.begin(), n1Neighbors.end(),
                     n2Neighbors.begin(), n2Neighbors.end(),
                     back_inserter(sharedNeighbors));
    // Get the indices of these two neighbors, and check if one is open
    int intersectionIndex1 =
            sharedNeighbors[0].first * this->getNumCols() + sharedNeighbors[0].second;
    int intersectionIndex2 =
            sharedNeighbors[1].first * this->getNumCols() + sharedNeighbors[1].second;
    if (cells[intersectionIndex1] || cells[intersectionIndex2])
        return false;
    return true;
}
