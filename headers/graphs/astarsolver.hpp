//
// Created by david on 10/2/21.
//

#ifndef MAZEMASTER_ASTARSOLVER_HPP
#define MAZEMASTER_ASTARSOLVER_HPP

#include <vector>
#include <map>
#include <functional>
#include "graph.hpp"


class AStarSolver {
private:
    // Convenience, otherwise lines would be 100 characters long
    typedef std::pair<int, int> node;

    // For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
    std::map<node, float> gScore;
    // For node n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current best guess as to
    // how short a path from start to finish can be if it goes through n.
    std::map<node, float> fScore;
    // Compares two nodes by fScores
    std::function<bool(const node&, const node&)> fScoreComparator;
    // Heap to store open set
    std::vector<node> openSet;
    // For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from start
    // to n currently known.
    std::map<node, node> cameFrom;
    // The heuristic function. h(n) estimates the cost to reach goal from node n.
    std::function<float(const node&)> heuristic;
    // graph to operate on
    Graph *graph;
    node start; // Start node
    node dest; // Dest node
private:
    /**
     * Performs pre-solving initializations. Must call before beginning to solve.
     */
    void init();
public:
    AStarSolver(Graph *graph, const node& start, const node& dest);
    /**
     * Default start and end are top left, and bottom right.
     */
    AStarSolver(Graph *graph);

    /**
     * Performs one step in the A* algorithm. Returns true if in this step a path
     * to the destination is successfully found, or if no such path exists in
     * the graph. Returns false if neither conclusion is reached.
     */
    bool doOneIteration();
    /**
     * Returns a vector storing the path from the start to the node currently closest
     * to the destination.
     */
    std::vector<node> getCurrentSolutionPath() const;
    /**
     * Clears all data/progress.
     */
     void clearData();

// STATIC METHODS
public:
    /**
     * Receives a GridGraph, a start and destination node and computes a path from
     * start to end, using A*. If no path exists, returns an empty vector.
     */
    static std::vector<node> solve(const Graph& graph, const node& start, const node& dest);

    void setStart(const node &loc);
    void setDest(const node &dest);
};

#endif //MAZEMASTER_ASTARSOLVER_HPP
