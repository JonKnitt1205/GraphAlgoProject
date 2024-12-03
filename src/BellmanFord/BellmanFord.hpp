#pragma once

#include "GraphTypes.hpp"

class BellmanFord {
public:
    BellmanFord() = delete;

    // takes adjlist and two vectors to store results into
    // returns false if negative cycle is detected
    static bool runBellmanFord(const Graph::AdjList& adjlist, std::vector<double>& distance, std::vector<size_t>& predecessor);
private:
    // set lists to correct size and initial values
    static void initLists(size_t nodeCount, std::vector<double>& distance, std::vector<size_t>& predecessor);

    // relaxes the edges one time, returns if the graph is still valid (no negative cycles)
    static bool relaxOnce(const Graph::AdjList& adjlist, std::vector<double>& distance, std::vector<size_t>& predecessor, size_t iteration);
};
