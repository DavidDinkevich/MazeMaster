//
// Created by david on 9/30/21.
//

#include "graphs/gridgraph.hpp"
#include <cmath>

using namespace std;

template<typename T>
GridGraph<T>::GridGraph(int numRows, int numCols) : numRows(numRows), numCols(numCols) {
    // Initialize cell array
    cells = new T[numRows * numCols];
}

template<typename T>
GridGraph<T>::~GridGraph() {
    delete [] cells;
}

template<typename T>
vector<pair<int, int>> GridGraph<T>::getNeighbors(const pair<int, int>& loc) const {
    vector<pair<int, int>> v;
    // North neighbor
    if (loc.first > 0)
        v.emplace_back(make_pair(loc.first - 1, loc.second));
    // Southern neighbor
    if (loc.first < numRows - 1)
        v.emplace_back(make_pair(loc.first + 1, loc.second));
    // Western neighbor
    if (loc.second > 0)
        v.emplace_back(make_pair(loc.first, loc.second - 1));
    // Eastern neighbor
    if (loc.second < numCols - 1)
        v.emplace_back(make_pair(loc.first, loc.second + 1));

    return v;
}

template<typename T>
float GridGraph<T>::getDistanceBetween(const pair<int, int> &n1, const pair<int, int> &n2) const {
    int dr = n1.first - n2.first;
    int dc = n1.second - n2.second;
    // Optimization: for cells that are sqrt(2) apart, which is often,
    // return precomputed result:
    if (abs(dr) == 1 && abs(dc) == 1)
        return 1.41421356237f; // sqrt(2)
    return sqrtf((float) (dr * dr + dc * dc));
}

template<typename T>
bool GridGraph<T>::cellsAreConnected(const pair<int, int> &n1, const pair<int, int> &n2) const {
    // Get indices of nodes in cells array
    int n1Index = n1.first * getNumCols() + n1.second;
    int n2Index = n2.first * getNumCols() + n2.second;
    if (n1Index == n2Index) // Same indices are not connected
        return false;
    int dr = n1.first - n2.first;
    int dc = n1.second - n2.second;
    // Check if nodes are adjacent
    return abs(dr) + abs(dc) == 1;
}

template<typename T>
void GridGraph<T>::setAllCells(T val) {
    for (int i = 0; i < numRows * numCols; i++) {
        cells[i] = val;
    }
}

template<typename T>
const T * GridGraph<T>::getCells() const {
    return cells;
}

template<typename T>
int GridGraph<T>::getNumRows() const {
    return numRows;
}

template<typename T>
int GridGraph<T>::getNumCols() const {
    return numCols;
}

template<typename T>
void GridGraph<T>::setCell(const pair<int, int> &loc, T val) {
    cells[loc.first * getNumCols() + loc.second] = val;
}

// FORCE COMPILER TO COMPILE TEMPLATES

template class GridGraph<int>;
template class GridGraph<bool>;