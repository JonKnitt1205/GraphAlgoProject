#pragma once

#include "GraphTypes.hpp"
#include <map>
#include <queue>

class AStar {
public:
    AStar() = delete;

    static void getPath(const Graph::AdjList& adjlist, const Graph::PosList& positions, std::vector<double>& distance, 
    std::vector<size_t>& predecessor, uint32_t dest);

private:
    // for use in priority queue comparisons
    struct Compare {
        Compare(const std::unordered_map<uint32_t, double>& fScores) : fScores(fScores) {}
        bool operator()(uint32_t a, uint32_t b) {
            return fScores.at(a) > fScores.at(b);
        }
        const std::unordered_map<uint32_t, double>& fScores;
    };

    // perform one iteration and return true if it is done
    static bool oneIteration(uint32_t destNode, std::priority_queue<uint32_t, std::vector<uint32_t>, Compare>& openSet, const Graph::AdjList& adjList, 
    std::unordered_map<uint32_t, double>& gScores, std::unordered_map<uint32_t, double>& fScores, std::vector<size_t>& parents, const Graph::PosList& positions);

    // initialize the scores to infinity
    static void initScores(std::unordered_map<uint32_t, double>& gScores, std::unordered_map<uint32_t, double>& fScores, const Graph::PosList& positions);

    // gets the heuristic using euclidean distance
    static double getHeuristic(uint32_t currNode, uint32_t dest, const Graph::PosList& positions);

    static void initParents(std::vector<size_t>& parents, uint32_t size);
};
