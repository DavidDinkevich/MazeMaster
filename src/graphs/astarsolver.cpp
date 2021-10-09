//
// Created by david on 10/2/21.
//

#include "graphs/astarsolver.hpp"
#include <vector>
#include <cmath>
#include <map>
#include <iostream>

using namespace std;

typedef pair<int, int> node; // Convenience, otherwise lines would be 100 characters long

// HELPER FUNCTIONS
namespace {
    vector<node> retraceSteps(const node &dest, const map<node, node> &map) {
        vector<node> path;
        node n = dest;
        while (map.contains(n)) {
            path.emplace_back(n);
            n = map.at(n);
        }
        reverse(path.begin(), path.end());
        return path;
    }
}

// END HELPER FUNCTIONS

// CLASS STATIC METHODS

vector<node> AStarSolver::solve(const Graph &graph, const node &start, const node &dest) {
    // For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
    map<node, float> gScore;
    // For node n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current best guess as to
    // how short a path from start to finish can be if it goes through n.
    map<node, float> fScore;
    // Compares two nodes by fScores
    auto fScoreComparator = [&](const node& p1, const node& p2) {
        return fScore[p1] > fScore[p2];
    };
    // Heap to store open set
    vector<node> openSet;
    // For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from start
    // to n currently known.
    map<node, node> cameFrom;
    // Put start node in map (with some random value)
    cameFrom[start] = make_pair(-1, -1);
    // The heuristic function. h(n) estimates the cost to reach goal from node n.
    auto heuristic = [&](const node& n) {
        int dr = abs(n.first - dest.first);
        int dc = abs(n.second - dest.second);
        return dr + dc; // Manhattan distance
    };
    // gScore[start] is defined as 0, and fScore[start] is the heuristic
    gScore[start] = 0.0f;
    fScore[start] = heuristic(start);
    openSet.emplace_back(start); // Kick off the process

    while (!openSet.empty()) {
        // Currently lowest fScore
        node current = openSet[0]; // Guaranteed to be non-empty
        if (current == dest) {
            return retraceSteps(dest, cameFrom);
        }
        // Remove the current node from open set
        pop_heap(openSet.begin(), openSet.end(), fScoreComparator);
        openSet.pop_back();
        // Go through neighbors of current node
        vector<node> neighbors = graph.getNeighbors(current);
        for (auto& neighb : neighbors) {
            // If we don't have a path to the neighbor, skip
            if (!graph.cellsAreConnected(current, neighb))
                continue;
            // Calculate would-be gScore for neighbor node
            float tentative_gScore = gScore[current] + graph.getDistanceBetween(current, neighb);
            // If we found a better way to get to the neighbor, or if this is the first
            // time visiting the neighbor, update
            if (!gScore.contains(neighb) || tentative_gScore < gScore[neighb]) {
                // This path to neighbor is better than any previous one. Record it!
                cameFrom[neighb] = current;
                gScore[neighb] = tentative_gScore; // Make tentative score official
                fScore[neighb] = tentative_gScore + heuristic(neighb); // Make fScore
                // If neighbor is not in the open set, push it
                if (find(openSet.begin(), openSet.end(), neighb) == openSet.end()) {
                    openSet.emplace_back(neighb);
                    push_heap(openSet.begin(), openSet.end(), fScoreComparator);
                }
            }
        }
    }
    return {}; // Return empty stack, no path

}

// END CLASS STATIC METHODS

// CLASS INSTANCE METHODS

AStarSolver::AStarSolver(Graph *graph, const node& start, const node& dest)
                        : graph(graph), start(start), dest(dest) {
    // Compares two nodes by fScores
    fScoreComparator = [&](const node& p1, const node& p2) {
        float fScore1 = fScore[p1];
        float fScore2 = fScore[p2];
//        if (fScore1 == fScore2)
//            return p1.first < p2.first;
        return fScore1 > fScore2;

//        if (fScore[p1] > fScore[p2])
//            return true;
//        return p1.first < p2.first;
    };
    // The heuristic function. h(n) estimates the cost to reach goal from node n.
    heuristic = [&](const node& n) {
        int dr = abs(n.first - this->dest.first);
        int dc = abs(n.second - this->dest.second);
//        return 4.0f * (dr + dc); // Manhattan distance
//        return dr*dr + dc*dc; // distance squared
//        return sqrtf(dr*dr + dc*dc); // SO MUCH SLOWER THAN WHEN REMOVING THE SQRT
//        D * (dx + dy) + (D2 - 2 * D) * min(dx, dy)
        return 2 *(1 * (dr + dc) + (1.414f - 2 * 1) * min(dr, dc));
    };
    // Prep for solve
    init();
}

AStarSolver::AStarSolver(Graph *graph)
: AStarSolver(
        graph,
        make_pair(0, 0),
        make_pair(graph->getNumRows() - 1, graph->getNumCols() - 1))
{
}

void AStarSolver::init() {
    // Put start node in map (with some random value)
    cameFrom[this->start] = make_pair(-1, -1);
    // gScore[start] is defined as 0, and fScore[start] is the heuristic
    gScore[this->start] = 0.0f;
    fScore[this->start] = heuristic(start);
    openSet.emplace_back(this->start); // Kick off the process
}

bool AStarSolver::doOneIteration() {
    // No path found
    if (openSet.empty())
        return true; // Conclude process
    else {
        // Currently lowest fScore
        node current = openSet[0]; // Guaranteed to be non-empty
//        if (openSet.size() >= 2 && fScore[current] == fScore[openSet[1]]) {
//            cout << "Tie: (" << current.first << ", " << current.second << "), (" << openSet[1].first << ", " << openSet[1].second << ")" << endl;
//        }


        if (current == dest)
            return true; // Conclude process
        // Remove the current node from open set
        pop_heap(openSet.begin(), openSet.end(), fScoreComparator);
        openSet.pop_back();
        // Go through neighbors of current node
        vector<node> neighbors = graph->getNeighbors(current);
        for (auto& neighb : neighbors) {
            // If we don't have a path to the neighbor, skip
            if (!graph->cellsAreConnected(current, neighb))
                continue;
            // Calculate would-be gScore for neighbor node
            float tentative_gScore = gScore[current] + graph->getDistanceBetween(current, neighb);
            // If we found a better way to get to the neighbor, or if this is the first
            // time visiting the neighbor, update
            if (!gScore.contains(neighb) || tentative_gScore < gScore[neighb]) {
                // This path to neighbor is better than any previous one. Record it!
                cameFrom[neighb] = current;
                gScore[neighb] = tentative_gScore; // Make tentative score official
                float h = heuristic(neighb);
                cout << tentative_gScore << ", " << h << " = " << tentative_gScore + h << endl;
                fScore[neighb] = tentative_gScore  + heuristic(neighb); // Make fScore
                // If neighbor is not in the open set, push it
                if (find(openSet.begin(), openSet.end(), neighb) == openSet.end()) {
                    openSet.emplace_back(neighb);
                    push_heap(openSet.begin(), openSet.end(), fScoreComparator);
                }
            }
        }
    }
    return false;
}

vector<node> AStarSolver::getCurrentSolutionPath() const {
    return openSet.empty() ? vector<node>{} : retraceSteps(openSet[0], cameFrom);
}

void AStarSolver::clearData() {
    openSet.clear();
    gScore.clear();
    fScore.clear();
    cameFrom.clear();
    // Prepare for next solve
    init();
}

void AStarSolver::setStart(const node& loc) {
    start.first = loc.first;
    start.second = loc.second;
}

void AStarSolver::setDest(const node &loc) {
    dest.first = loc.first;
    dest.second = loc.second;
}

// END CLASS INSTANCE METHODS